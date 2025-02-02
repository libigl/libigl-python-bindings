#include "default_types.h"
#include <igl/AABB.h>
#include <igl/list_to_matrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>
namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  template <typename AABB>
  void aabb_init(
    AABB &tree,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele)
  {
    tree.init(V,Ele);
  }
  template <typename AABB>
  auto find(
    AABB &tree,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::RowVectorXN> &q,
    const bool first)
  {
    if(Ele.cols() != V.cols()+1)
    {
      throw std::runtime_error("find: Ele must have V.cols()+1 columns");
    }
    std::vector<int> vec_int = tree.find(V,Ele,q,first);
    std::vector<Integer> vec(vec_int.begin(),vec_int.end());
    return vec;
  }

  template <typename AABB>
  auto squared_distance(
    AABB &tree,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::MatrixXN> &P)
  {
    Eigen::VectorXN sqrD;
    Eigen::VectorXI I;
    Eigen::MatrixXN C;
    tree.squared_distance(V,Ele,P,sqrD,I,C);
    return std::make_tuple(sqrD,I,C);
  }

  template <typename AABB>
  auto intersect_ray_first(
    AABB &tree,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::MatrixXN> &orig,
    const nb::DRef<const Eigen::MatrixXN> &dir,
    const Numeric min_t)
  {
    Eigen::VectorXI I;
    Eigen::VectorXN T;
    Eigen::MatrixXN UV;
    tree.intersect_ray(V,Ele,orig,dir,min_t,I,T,UV);
    return std::make_tuple(I,T,UV);
  }

  template <typename AABB>
  auto intersect_ray(
    AABB &tree,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::MatrixXN> &orig,
    const nb::DRef<const Eigen::MatrixXN> &dir)
  {
    std::vector<std::vector<igl::Hit<Numeric>>> hits;
    tree.intersect_ray(V,Ele,orig,dir,hits);
    std::vector<std::vector<std::tuple<Integer,Numeric,Numeric,Numeric>>> out;
    for(const auto &hit : hits)
    {
      std::vector<std::tuple<Integer,Numeric,Numeric,Numeric>> hit_out;
      for(const auto &h : hit)
      {
        hit_out.push_back(std::make_tuple(h.id,h.t,h.u,h.v));
      }
      out.push_back(hit_out);
    }

    return out;
  }
}

// Bind the wrapper to the Python module
void bind_AABB(nb::module_ &m)
{
  typedef igl::AABB<nb::DRef<const Eigen::MatrixXN>,3> AABBN3;
  nb::class_<AABBN3>(m, "AABB")
    .def(nb::init<>())
    .def("init", &pyigl::aabb_init<AABBN3>, "V"_a, "Ele"_a)
    .def("find", &pyigl::find<AABBN3>, "V"_a, "Ele"_a, "q"_a, "first"_a=false)
    .def("squared_distance", &pyigl::squared_distance<AABBN3>, "V"_a, "Ele"_a, "P"_a)
    .def("intersect_ray_first",&pyigl::intersect_ray_first<AABBN3>, "V"_a, "Ele"_a, "orig"_a, "dir"_a, "min_t"_a=std::numeric_limits<Numeric>::infinity())
    .def("intersect_ray",&pyigl::intersect_ray<AABBN3>, "V"_a, "Ele"_a, "orig"_a, "dir"_a)
    ;
}




