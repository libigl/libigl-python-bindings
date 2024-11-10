#include "default_types.h"
#include <igl/cotmatrix_entries.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  Eigen::MatrixXN cotmatrix_entries_VF(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN C;
    igl::cotmatrix_entries(V,F,C);
    return C;
  }
  Eigen::MatrixXN cotmatrix_entries_l(
    const nb::DRef<const Eigen::MatrixXN> &l)
  {
    Eigen::MatrixXN C;
    igl::cotmatrix_entries(l,C);
    return C;
  }
}

void bind_cotmatrix_entries(nb::module_ &m)
{
  m.def(
    "cotmatrix_entries",
    &pyigl::cotmatrix_entries_VF,
    "V"_a,
    "F"_a,
R"(Compute the cotangent contributions for each angle in a mesh.

@param[in] V  #V by dim matrix of vertex positions
@param[in] F  #F by {3|4} matrix of {triangle|tetrahedra} indices into V (optional)

@return C  #F by {3|6} matrix of cotangent contributions
    - For triangles, columns correspond to edges [1,2], [2,0], [0,1]
    - For tets, columns correspond to edges [1,2], [2,0], [0,1], [3,0], [3,1], [3,2])");
  m.def(
    "cotmatrix_entries",
    &pyigl::cotmatrix_entries_l,
    "l"_a,
R"(Compute the cotangent contributions for each angle in a mesh.

@param[in] l  #F by 3 matrix of triangle edge lengths (optional, alternative to F)
@return C  #F by {3|6} matrix of cotangent contributions
    - For triangles, columns correspond to edges [1,2], [2,0], [0,1]
    - For tets, columns correspond to edges [1,2], [2,0], [0,1], [3,0], [3,1], [3,2])");
}
