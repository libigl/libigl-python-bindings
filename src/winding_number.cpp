#include "default_types.h"
#include <igl/winding_number.h>
#include <igl/signed_angle.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Binding for winding_number over multiple query points
  auto winding_number(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &O)
  {
    Eigen::VectorXN W;
    // The DerivedF on WindingNumberAABB and WindingNumberTree is 
    // broken and must be MatrixXi.
    // Similarly DerivedV is broken and probably has to be MatrixX*.
    Eigen::MatrixXN V_cpy = V;
    Eigen::MatrixXi F_cpy = F.cast<int>();
    igl::winding_number(V_cpy, F_cpy, O, W);
    return W;
  }
  // Binding for winding_number over multiple query points
  Numeric winding_number_single(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &o)
  {
    return igl::winding_number(V, F, o.transpose());
  }

}

// Bind the wrapper to the Python module
void bind_winding_number(nb::module_ &m)
{
  m.def(
    "winding_number",
    &pyigl::winding_number,
    "V"_a,
    "F"_a,
    "O"_a,
    R"(Computes the generalized winding number at each query point with respect to the mesh.

    @param[in] V  #V by dim list of mesh vertex positions
    @param[in] F  #F by dim list of mesh facets as indices into rows of V
    @param[in] O  #O by dim list of query points
    @return Vector of winding numbers for each query point)");
  m.def(
    "winding_number",
    &pyigl::winding_number_single,
    "V"_a,
    "F"_a,
    "o"_a,
    R"(Computes the generalized winding number at each query point with respect to the mesh.

    @param[in] V  #V by dim list of mesh vertex positions
    @param[in] F  #F by dim list of mesh facets as indices into rows of V
    @param[in] o  dim-vector of query point
    @return winding number)");
}
