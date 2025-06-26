#include "default_types.h"
#include <igl/harmonic.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

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
  auto harmonic_integrated_from_laplacian_and_mass(
    const Eigen::SparseMatrixN &L,
    const Eigen::SparseMatrixN &M,
    const int k)
  {
    Eigen::SparseMatrixN Q;
    igl::harmonic(L, M, k, Q);
    return Q;
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
  m.def(
    "harmonic_integrated_from_laplacian_and_mass",
    &pyigl::harmonic_integrated_from_laplacian_and_mass,
    "L"_a, 
    "M"_a, 
    "k"_a, 
R"(Build the discrete k-harmonic operator (computing integrated quantities). 
That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x.

@param[in] L  #V by #V discrete (integrated) Laplacian
@param[in] M  #V by #V mass matrix
@param[in] k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)
@return Q  #V by #V discrete (integrated) k-Laplacian)");
}