#include "default_types.h"
#include <igl/boundary_facets.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  nb::object boundary_facets(
    const nb::DRef<const Eigen::MatrixXI> &T,
    bool return_J,
    bool return_K)
  {
    Eigen::MatrixXI F;
    Eigen::VectorXI J;
    Eigen::VectorXI K;
    igl::boundary_facets(T,F,J,K);
    if(return_J && return_K)
    {
      return nb::make_tuple(F,J,K);
    }else if(return_J)
    {
      return nb::make_tuple(F,J);
    }else if(return_K)
    {
      return nb::make_tuple(F,K);
    }
    return nb::cast(F);
  }
}

// Bind the wrapper to the Python module
void bind_boundary_facets(nb::module_ &m)
{
  m.def(
    "boundary_facets",
    &pyigl::boundary_facets, 
    "T"_a,
    "return_J"_a=false,
    "return_K"_a=false,
R"(Determine boundary faces (edges) of tetrahedra (triangles) stored in T
(analogous to qptoolbox's `outline` and `boundary_faces`).

@param[in] T  tetrahedron (triangle) index list, m by 4 (3), where m is the number of tetrahedra
@param[out] F  list of boundary faces, n by 3 (2), where n is the number
  of boundary faces. Faces are oriented so that igl::centroid(V,F,…)
computes the same sign volume as igl::volume(V,T)
@param[out] J  list of indices into T, n by 1
@param[out] K  list of indices revealing across from which vertex is this facet)"
    );
}




