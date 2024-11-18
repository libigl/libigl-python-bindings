#include "default_types.h"
#include <igl/massmatrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto massmatrix(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const igl::MassMatrixType type)
  {
    Eigen::SparseMatrixN M;
    igl::massmatrix(V,F,type,M);
    return M;
  }
}

// Bind the wrapper to the Python module
void bind_massmatrix(nb::module_ &m)
{
  m.def(
    "massmatrix",
    &pyigl::massmatrix, 
    "V"_a, 
    "F"_a,
    "type"_a=igl::MASSMATRIX_TYPE_DEFAULT,
R"(Constructs the mass (area) matrix for a given mesh (V,F).

@tparam DerivedV  derived type of eigen matrix for V (e.g. derived from
    MatrixXd)
@tparam DerivedF  derived type of eigen matrix for F (e.g. derived from
    MatrixXi)
@tparam Scalar  scalar type for eigen sparse matrix (e.g. double)
@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by simplex_size list of mesh elements (triangles or tetrahedra)
@param[in] type  one of the following ints:
    MASSMATRIX_TYPE_BARYCENTRIC  barycentric {default for tetrahedra}
    MASSMATRIX_TYPE_VORONOI voronoi-hybrid {default for triangles}
    MASSMATRIX_TYPE_FULL full
@param[out] M  #V by #V mass matrix

\see cotmatrix)"
    );
}
