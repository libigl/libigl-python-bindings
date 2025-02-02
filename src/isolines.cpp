#include "default_types.h"
#include <igl/isolines.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto isolines(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &S,
    const nb::DRef<const Eigen::VectorXN> &vals)
  {
    Eigen::MatrixXN iV;
    Eigen::MatrixXI iE;
    Eigen::VectorXI I;
    igl::isolines(V,F,S,vals,iV,iE,I);
    return std::make_tuple(iV,iE,I);
  }
}

// Bind the wrapper to the Python module
void bind_isolines(nb::module_ &m)
{
  m.def(
    "isolines",
    &pyigl::isolines, 
    "V"_a, 
    "F"_a,
    "S"_a,
    "vals"_a,
R"(Compute isolines of a scalar field on a triangle mesh.

Isolines may cross perfectly at vertices. The output should not contain
degenerate segments (so long as the input does not contain degenerate
faces). The output segments are *oriented* so that isolines curl
counter-clockwise around local maxima (i.e., for 2D scalar fields). Unless
an isoline hits a boundary, it should be a closed loop. Isolines may run
perfectly along boundaries. Isolines should appear just "above" constants
regions.

@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by 3 list of mesh triangle indices into V
@param[in] S  #S by 1 list of per-vertex scalar values
@param[in] vals  #vals by 1 list of values to compute isolines for
@param[out] iV  #iV by dim list of isoline vertex positions
@param[out] iE  #iE by 2 list of edge indices into iV
@param[out] I  #iE by 1 list of indices into vals indicating which value
  each segment belongs to

\see isolines_intrinsic, edge_crossings)");
}



