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
  nb::object barycentric_coordinates(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &A,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::MatrixXN> &D)
  {
    Eigen::MatrixXN L;
    if(D.size()>0)
    {
      igl::barycentric_coordinates(P, A, B, C, D, L);
    }else
    {
      igl::barycentric_coordinates(P, A, B, C, L);
    }
    return nb::cast(std::move(L));
  }
}

// Bind the wrapper to the Python module
void bind_barycentric_coordinates(nb::module_ &m)
{
  m.def(
    "barycentric_coordinates",
    &pyigl::barycentric_coordinates,
    "P"_a,
    "A"_a,
    "B"_a,
    "C"_a,
    "D"_a=Eigen::MatrixXN(),
R"(Compute barycentric coordinates of each point in a corresponding triangle/tetrahedron.

@param[in] P  #P by 3 Query points in 3d
@param[in] A  #P by 3 (Tri|Tet) corners in 3d
@param[in] B  #P by 3 (Tri|Tet) corners in 3d
@param[in] C  #P by 3 (Tri|Tet) corners in 3d
@param[in] D  #P by 3 Tet corners in 3d
@param[out] L  #P by (3|4) list of barycentric coordinates
  )"
    );
}


