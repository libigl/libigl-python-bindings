#include "default_types.h"
#include <igl/barycenter.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for barycenter function
  auto barycenter(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN BC;
    igl::barycenter(V, F, BC);
    return BC;
  }
}

// Bind the wrapper to the Python module
void bind_barycenter(nb::module_ &m)
{
  m.def(
    "barycenter",
    &pyigl::barycenter,
    "V"_a, "F"_a,
R"(Computes the barycenter of every simplex.

@param[in] V  #V x dim matrix of vertex coordinates
@param[in] F  #F x simplex_size  matrix of indices of simplex corners into V
@param[out] BC  #F x dim matrix of 3d vertices)"
    );
}

