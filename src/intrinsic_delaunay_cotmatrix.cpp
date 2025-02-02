#include "default_types.h"
#include <igl/intrinsic_delaunay_cotmatrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto intrinsic_delaunay_cotmatrix(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::SparseMatrixN L;
    Eigen::MatrixXN il;
    Eigen::MatrixXI iF;
    igl::intrinsic_delaunay_cotmatrix(V,F,L,il,iF);
    return std::make_tuple(L,il,iF);
  }
}

// Bind the wrapper to the Python module
void bind_intrinsic_delaunay_cotmatrix(nb::module_ &m)
{
  m.def(
    "intrinsic_delaunay_cotmatrix",
    &pyigl::intrinsic_delaunay_cotmatrix, 
    "V"_a, 
    "F"_a,
R"(
Computes the discrete cotangent Laplacian of a mesh after converting it
into its intrinsic Delaunay triangulation (see, e.g., [Fisher et al.
2007].

@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by 3 list of mesh elements (triangles or tetrahedra)
@param[out] L  #V by #V cotangent matrix, each row i corresponding to V(i,:)
@param[out] l_intrinsic  #F by 3 list of intrinsic edge-lengths used to compute L
@param[out] F_intrinsic  #F by 3 list of intrinsic face indices used to compute L

\see intrinsic_delaunay_triangulation, cotmatrix, cotmatrix_intrinsic)");
}
