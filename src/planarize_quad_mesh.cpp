#include "default_types.h"
#include <igl/planarize_quad_mesh.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto planarize_quad_mesh(
    const nb::DRef<const Eigen::MatrixXN> &Vin,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const int maxIter,
    const Numeric threshold)
  {
    // Vout must share Vin's (deduced) type, so pass a concrete copy of the input
    Eigen::MatrixXN Vin_copy = Vin;
    Eigen::MatrixXN Vout;
    igl::planarize_quad_mesh(Vin_copy, F, maxIter, threshold, Vout);
    return Vout;
  }
}

void bind_planarize_quad_mesh(nb::module_ &m)
{
  m.def(
    "planarize_quad_mesh",
    &pyigl::planarize_quad_mesh,
    "Vin"_a,
    "F"_a,
    "maxIter"_a = 100,
    "threshold"_a = 0.005,
R"(Planarize a quad mesh, moving vertices so that each quad becomes as planar
as possible while staying close to the original surface.

@param[in] Vin  #V by 3 list of input mesh vertex positions
@param[in] F  #F by 4 list of quad face indices into rows of Vin
@param[in] maxIter  maximum number of optimization iterations
@param[in] threshold  planarity threshold at which to stop
@param[out] Vout  #V by 3 list of planarized vertex positions)");
}
