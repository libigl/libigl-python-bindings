#include "default_types.h"
#include <igl/lscm.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto lscm(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXI> &b,
    const nb::DRef<const Eigen::MatrixXN> &bc)
  {
    Eigen::MatrixXN V_uv;
    Eigen::SparseMatrix<Numeric> Q;
    if(!igl::lscm(V, F, b, bc, V_uv, Q))
    {
      throw std::runtime_error("igl::lscm failed");
    }
    return std::make_tuple(V_uv, Q);
  }
}

// Bind the wrapper to the Python module
void bind_lscm(nb::module_ &m)
{
  m.def(
    "lscm",
    &pyigl::lscm,
    "V"_a,
    "F"_a,
    "b"_a,
    "bc"_a,
    R"(Compute a Least-squares conformal map parametrization.

    @param[in] V  #V by 3 list of mesh vertex positions
    @param[in] F  #F by 3 list of mesh faces (must be triangles)
    @param[in] b  #b list of boundary indices into V
    @param[in] bc #b by 2 list of boundary values
    @param[out] V_uv #V by 2 list of 2D mesh vertex positions in UV space
    @param[out] Q  #Vx2 by #Vx2 symmetric positive semi-definite matrix for computing LSCM energy
    @return Tuple containing:
      - V_uv: UV coordinates of vertices
      - Q: Symmetric positive semi-definite matrix for LSCM energy)"
  );
}

