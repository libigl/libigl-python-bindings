#include "default_types.h"
#include <igl/barycentric_coordinates.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <limits>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for barycentric_coordinates function
  auto barycentric_coordinates_PABC(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &A,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXN> &C)
  {
    Eigen::MatrixXN L;
    igl::barycentric_coordinates(P, A, B, C, L);
    return L;
  }
  auto barycentric_coordinates_PABCD(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &A,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::MatrixXN> &D)
  {
    Eigen::MatrixXN L;
    igl::barycentric_coordinates(P, A, B, C, D, L);
    return L;
  }
}

// Bind the wrapper to the Python module
void bind_barycentric_coordinates(nb::module_ &m)
{
  m.def(
    "barycentric_coordinates",
    &pyigl::barycentric_coordinates_PABC,
    "P"_a,
    "A"_a,
    "B"_a,
    "C"_a,
R"(Compute barycentric coordinates of each point in a corresponding triangle

@param[in] P  #P by 3 Query points in 3d
@param[in] A  #P by 3 Tri corners in 3d
@param[in] B  #P by 3 Tri corners in 3d
@param[in] C  #P by 3 Tri corners in 3d
@param[out] L  #P by 3 list of barycentric coordinates
  )"
    );
  m.def(
    "barycentric_coordinates",
    &pyigl::barycentric_coordinates_PABCD,
    "P"_a,
    "A"_a,
    "B"_a,
    "C"_a,
    "D"_a,
R"(Compute barycentric coordinates of each point in a corresponding tetrhedron

@param[in] P  #P by 3 Query points in 3d
@param[in] A  #P by 3 Tet corners in 3d
@param[in] B  #P by 3 Tet corners in 3d
@param[in] C  #P by 3 Tet corners in 3d
@param[in] D  #P by 3 Tet corners in 3d
@param[out] L  #P by 3 list of barycentric coordinates
  )"
    );
}


