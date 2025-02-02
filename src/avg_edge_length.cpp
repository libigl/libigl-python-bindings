#include "default_types.h"
#include <igl/avg_edge_length.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto avg_edge_length(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    return (Numeric)igl::avg_edge_length(V,F);
  }
}

void bind_avg_edge_length(nb::module_ &m)
{
  m.def(
    "avg_edge_length",
    &pyigl::avg_edge_length, 
    "V"_a, 
    "F"_a,
R"(Constructs the cotangent stiffness matrix (discrete laplacian) for a given
mesh (V,F).

  @tparam DerivedV  derived type of eigen matrix for V (e.g. derived from
    MatrixXd)
  @tparam DerivedF  derived type of eigen matrix for F (e.g. derived from
    MatrixXi)
  @tparam Scalar  scalar type for eigen sparse matrix (e.g. double)
  @param[in] V  #V by dim list of mesh vertex positions
  @param[in] F  #F by simplex_size list of mesh elements (triangles or tetrahedra)
  @param[out] L  #V by #V cotangent matrix, each row i corresponding to V(i,:))");

}
