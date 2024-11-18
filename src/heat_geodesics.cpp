#include "default_types.h"
#include <igl/heat_geodesics.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  void heat_geodesics_precompute_t(
    const nb::DRef<const Eigen::MatrixXN>  &V,
    const nb::DRef<const Eigen::MatrixXI>  &F,
    const Numeric t,
    igl::HeatGeodesicsData<Numeric> &data)
  {
    if(!igl::heat_geodesics_precompute(V,F,t,data))
    {
      throw std::runtime_error("heat_geodesics: Precomputation failed.");
    }
  }
  // Obnoxious way to have optional t
  void heat_geodesics_precompute(
    const nb::DRef<const Eigen::MatrixXN>  &V,
    const nb::DRef<const Eigen::MatrixXI>  &F,
    igl::HeatGeodesicsData<Numeric> &data)
  {
    if(!igl::heat_geodesics_precompute(V,F,data))
    {
      throw std::runtime_error("heat_geodesics: Precomputation failed.");
    }
  }

  auto heat_geodesics_solve(
    const igl::HeatGeodesicsData<Numeric> &data,
    const nb::DRef<const Eigen::VectorXI> &gamma)
  {
    Eigen::VectorXN D;
    igl::heat_geodesics_solve(data, gamma, D);
    return D;
  }

}

// Bind the wrapper to the Python module
void bind_heat_geodesics(nb::module_ &m)
{
  nb::class_<igl::HeatGeodesicsData<Numeric>>(m, "HeatGeodesicsData")
    .def(nb::init<>())
    .def_rw("use_intrinsic_delaunay", &igl::HeatGeodesicsData<Numeric>::use_intrinsic_delaunay)
    ;

  m.def("heat_geodesics_precompute", 
      &pyigl::heat_geodesics_precompute_t,
      "V"_a, "F"_a, "t"_a, "data"_a,
      R"(Precompute factorized solvers for computing a fast approximation of
geodesic distances on a mesh (V,F). [Crane et al. 2013]

@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by 3 list of mesh face indices into V
@param[in] t  "heat" parameter (smaller --> more accurate, less stable)
@param[out] data  precomputation data (see heat_geodesics_solve)
      )");
  m.def("heat_geodesics_precompute", 
      &pyigl::heat_geodesics_precompute,
      "V"_a, "F"_a, "data"_a,
      R"(Precompute factorized solvers for computing a fast approximation of
geodesic distances on a mesh (V,F). [Crane et al. 2013]

@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by 3 list of mesh face indices into V
@param[out] data  precomputation data (see heat_geodesics_solve)
      )");
  m.def("heat_geodesics_solve", 
      &pyigl::heat_geodesics_solve,
      "data"_a,
      "gamma"_a,
      R"(Compute fast approximate geodesic distances using precomputed data from a
set of selected source vertices (gamma).

@param[in] data  precomputation data (see heat_geodesics_precompute)
@param[in] gamma  #gamma list of indices into V of source vertices
@param[out] D  #V list of distances to gamma 

\fileinfo
      )");
}
