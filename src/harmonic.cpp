#include "default_types.h"
#include <igl/harmonic.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for the harmonic function
  auto harmonic(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXI> &b,
    const nb::DRef<const Eigen::MatrixXN> &bc,
    const int k)
  {
    Eigen::MatrixXN W;
    if(!igl::harmonic(V, F, b, bc, k, W))
    {
      throw std::runtime_error("Failed to compute harmonic map");
    }
    return W;
  }
}

// Bind the wrapper to the Python module
void bind_harmonic(nb::module_ &m)
{
  m.def(
    "harmonic",
    &pyigl::harmonic,
    "V"_a, 
    "F"_a, 
    "b"_a, 
    "bc"_a, 
    "k"_a, 
R"(Compute k-harmonic weight functions "coordinates".

@param[in] V  #V by dim vertex positions
@param[in] F  #F by simplex-size list of element indices
@param[in] b  #b boundary indices into V
@param[in] bc #b by #W list of boundary values
@param[in] k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)
@return W  #V by #W list of weights)");
}
