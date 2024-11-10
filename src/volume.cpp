#include "default_types.h"
#include <igl/volume.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto volume_VT(
    const nb::DRef<const Eigen::MatrixXN> &V = Eigen::MatrixXN(),
    const nb::DRef<const Eigen::MatrixXI> &T = Eigen::MatrixXI())
  {
    Eigen::VectorXN vol;
    igl::volume(V, T, vol);
    return vol;
  }
  auto volume_L(
    const nb::DRef<const Eigen::MatrixXN> &L = Eigen::MatrixXN())
  {
    Eigen::VectorXN vol;
    igl::volume(L, vol);
    return vol;
  }
  auto volume_ABCD(
    const nb::DRef<const Eigen::MatrixXN> &A = Eigen::MatrixXN(),
    const nb::DRef<const Eigen::MatrixXN> &B = Eigen::MatrixXN(),
    const nb::DRef<const Eigen::MatrixXN> &C = Eigen::MatrixXN(),
    const nb::DRef<const Eigen::MatrixXN> &D = Eigen::MatrixXN())
  {
    Eigen::VectorXN vol;
    igl::volume(A, B, C, D, vol);
    return vol;
  }

}

// Bind the wrapper to the Python module
void bind_volume(nb::module_ &m)
{
  m.def(
    "volume",
    &pyigl::volume_VT,
    "V"_a = Eigen::MatrixXN(),
    "T"_a = Eigen::MatrixXI(),
R"(Compute volume for tetrahedrons in various input formats.

@param[in] V  #V by dim list of vertex positions or first corner positions
@param[in] T  #T by 4 list of tet indices 
@return vol #T list of tetrahedron volumes)");
  m.def(
    "volume",
    &pyigl::volume_L,
    "L"_a = Eigen::MatrixXN(),
R"(Compute volume for tetrahedrons in various input formats.

@param[in] L  #V by 6 list of edge lengths (see edge_lengths)
@return vol #T list of tetrahedron volumes)");
  m.def(
    "volume",
    &pyigl::volume_ABCD,
    "A"_a = Eigen::MatrixXN(),
    "B"_a = Eigen::MatrixXN(),
    "C"_a = Eigen::MatrixXN(),
    "D"_a = Eigen::MatrixXN(),
R"(Compute volume for tetrahedrons in various input formats.

@param[in] A  #A by dim list of vertex positions or first corner positions
@param[in] B  #A by dim list of second corner positions 
@param[in] C  #A by dim list of third corner positions 
@param[in] D  #A by dim list of fourth corner positions 

@return vol #T list of tetrahedron volumes)");
}
