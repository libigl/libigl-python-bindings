#include "default_types.h"
#include <igl/embree/EmbreeIntersector.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>
namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto embree_intersect_ray_first(
    igl::embree::EmbreeIntersector &ei,
    const Eigen::RowVector3f& origin,
    const Eigen::RowVector3f& direction,
    const float tnear,
    const float tfar)
  {
    igl::Hit<float> h;
    bool ret = ei.intersectRay(origin,direction,h,tnear,tfar);
    if(!ret){ h.id = -1; }
    return std::make_tuple(
      (Integer)h.id,
      (Numeric)h.t,
      (Numeric)h.u,
      (Numeric)h.v);
  }

  auto embree_intersect_ray(
    igl::embree::EmbreeIntersector &ei,
    const Eigen::RowVector3f& origin,
    const Eigen::RowVector3f& direction,
    const float tnear,
    const float tfar)
  {
    std::vector<igl::Hit<float>> hits;
    int num_rays;
    ei.intersectRay(origin,direction,hits,num_rays,tnear,tfar);
    std::vector<std::tuple<Integer,Numeric,Numeric,Numeric>> out;
    for(const auto &h : hits)
    {
      out.emplace_back(h.id,h.t,h.u,h.v);
    }
    return std::make_tuple(out,(Integer)num_rays);
  }
}

void bind_EmbreeIntersector(nb::module_ &m)
{
  using igl::embree::EmbreeIntersector;
  nb::class_<EmbreeIntersector>(m,"EmbreeIntersector")
    .def(nb::init<>())
    .def("init", nb::overload_cast<const EmbreeIntersector::PointMatrixType &,const EmbreeIntersector::FaceMatrixType &, bool>(&EmbreeIntersector::init), "V"_a, "F"_a, "isStatic"_a=false)
    .def("intersectRay_first", &pyigl::embree_intersect_ray_first, "origin"_a, "direction"_a, "tnear"_a=0, "tfar"_a=std::numeric_limits<float>::infinity())
    .def("intersectRay", &pyigl::embree_intersect_ray, "origin"_a, "direction"_a, "tnear"_a=0, "tfar"_a=std::numeric_limits<float>::infinity())
    ;
}
