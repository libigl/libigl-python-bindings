#include "default_types.h"
#include <igl/crouzeix_raviart_cotmatrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto crouzeix_raviart_cotmatrix(
    const nb::DRef<const Eigen::MatrixXN> & V,
    const nb::DRef<const Eigen::MatrixXI> & F,
    const nb::DRef<const Eigen::MatrixXI> & E,
    const nb::DRef<const Eigen::VectorXI> & EMAP)
  {
    Eigen::SparseMatrix<Numeric> L;
    igl::crouzeix_raviart_cotmatrix(V, F, E, EMAP, L);
    return L;
  }
}

void bind_crouzeix_raviart_cotmatrix(nb::module_ &m)
{
  m.def("crouzeix_raviart_cotmatrix", &pyigl::crouzeix_raviart_cotmatrix,
    "V"_a,
    "F"_a,
    "E"_a,
    "EMAP"_a,
    R"(Compute the Crouzeix-Raviart cotangent stiffness matrix.
See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,
Harmon, Zorin, Grinspun 2007]
@param[in] V  #V by dim list of vertex positions
@param[in] F  #F by 3/4 list of triangle/tetrahedron indices
@param[in] E  #E by 2/3 list of edges/faces
@param[in] EMAP  #F*3/4 list of indices mapping allE to E
@param[out] L  #E by #E edge/face-based diagonal cotangent matrix
\see crouzeix_raviart_massmatrix)");
}
