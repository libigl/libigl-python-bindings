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
  void init(
    AABB &tree,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele)
  {
    tree.init(V,Ele);
  }
  template <typename AABB>
  nb::object find(
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
    if(first)
    {
      return vec.size() ? nb::cast(vec[0]) : nb::none();
    }else
    {
      return nb::cast(std::move(vec));
    }
  }

  template <typename AABB>
  nb::object squared_distance(
    AABB &tree,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::MatrixXN> &P,
    const bool return_I,
    const bool return_C)
  {
    Eigen::VectorXN sqrD;
    Eigen::VectorXI I;
    Eigen::MatrixXN C;
    tree.squared_distance(V,Ele,P,sqrD,I,C);
    if(return_I && return_C)
    {
      return nb::make_tuple(sqrD,I,C);
    }else if(return_I)
    {
      return nb::make_tuple(sqrD,I);
    }else if(return_C)
    {
      return nb::make_tuple(sqrD,C);
    }
    return nb::cast(std::move(sqrD));
  }

  template <typename AABB>
  nb::object intersect_ray(
    AABB &tree,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::MatrixXN> &orig,
    const nb::DRef<const Eigen::MatrixXN> &dir,
    const Numeric min_t,
    const bool first)
  {
    if(first)
    {

      Eigen::VectorXI I;
      Eigen::VectorXN T;
      Eigen::MatrixXN UV;
      tree.intersect_ray(V,Ele,orig,dir,min_t,I,T,UV);
      return nb::make_tuple(I,T,UV);
    }else
    {
      if(std::isfinite(min_t))
      {
        throw std::runtime_error("intersect_ray: min_t only supported for first=true");
      }
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

      return nb::cast(std::move(out));
    }
  }
}

// Bind the wrapper to the Python module
void bind_AABB(nb::module_ &m)
{
  typedef igl::AABB<nb::DRef<const Eigen::MatrixXN>,3> AABBN3;
  nb::class_<AABBN3>(m, "AABB")
    .def(nb::init<>())
    .def("init", &pyigl::init<AABBN3>, "V"_a, "Ele"_a)
    .def("find", &pyigl::find<AABBN3>, "V"_a, "Ele"_a, "q"_a, "first"_a=false)
    .def("squared_distance", &pyigl::squared_distance<AABBN3>, "V"_a, "Ele"_a, "P"_a, "return_I"_a=false,"return_C"_a=false)
    .def("intersect_ray",&pyigl::intersect_ray<AABBN3>, "V"_a, "Ele"_a, "orig"_a, "dir"_a, "min_t"_a=std::numeric_limits<Numeric>::infinity(), "first"_a=false)
    ;
}




