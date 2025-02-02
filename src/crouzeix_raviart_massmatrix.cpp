#include "default_types.h"
#include <igl/crouzeix_raviart_massmatrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto crouzeix_raviart_massmatrix(
    const nb::DRef<const Eigen::MatrixXN> & V,
    const nb::DRef<const Eigen::MatrixXI> & F,
    const nb::DRef<const Eigen::MatrixXI> & E,
    const nb::DRef<const Eigen::VectorXI> & EMAP)
  {
    Eigen::SparseMatrix<Numeric> L;
    igl::crouzeix_raviart_massmatrix(V, F, E, EMAP, L);
    return L;
  }
}

void bind_crouzeix_raviart_massmatrix(nb::module_ &m)
{
  m.def("crouzeix_raviart_massmatrix", &pyigl::crouzeix_raviart_massmatrix,
    "V"_a,
    "F"_a,
    "E"_a,
    "EMAP"_a,
    R"(CROUZEIX_RAVIART_MASSMATRIX Compute the Crouzeix-Raviart mass matrix where
M(e,e) is just the sum of the areas of the triangles on either side of an
edge e.
See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,
Harmon, Zorin, Grinspun 2007]
@param[in] V  #V by dim list of vertex positions
@param[in] F  #F by 3/4 list of triangle/tetrahedron indices
@param[in] E  #E by 2/3 list of edges/faces
@param[in] EMAP  #F*3/4 list of indices mapping allE to E
@param[out] M  #E by #E edge/face-based diagonal mass matrix
\see crouzeix_raviart_cotmatrix)");
}
