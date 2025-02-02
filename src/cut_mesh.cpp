#include "default_types.h"
#include <igl/cut_mesh.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto cut_mesh(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXB> &C)
  {
    Eigen::MatrixXN Vn;
    Eigen::MatrixXI Fn;
    Eigen::VectorXI I;
    igl::cut_mesh(V,F,C,Vn,Fn,I);
    return std::make_tuple(Vn,Fn,I);
  }

}

// Bind the wrapper to the Python module
void bind_cut_mesh(nb::module_ &m)
{
  m.def(
    "cut_mesh",
    &pyigl::cut_mesh, 
    "V"_a, 
    "F"_a,
    "C"_a,
R"(Given a mesh and a list of edges that are to be cut, the function
generates a new disk-topology mesh that has the cuts at its boundary.


\note Assumes mesh is edge-manifold.
@param[in,out] V  #V by 3 list of the vertex positions
@param[in,out] F  #F by 3 list of the faces
@param[in] cuts  #F by 3 list of boolean flags, indicating the edges that need to
    be cut (has 1 at the face edges that are to be cut, 0 otherwise)
@param[out]  Vn  #V by 3 list of the vertex positions of the cut mesh. This matrix
    will be similar to the original vertices except some rows will be
    duplicated.
@param[out]  Fn  #F by 3 list of the faces of the cut mesh(must be triangles). This
    matrix will be similar to the original face matrix except some indices
    will be redirected to point to the newly duplicated vertices.
@param[out]  I   #V by 1 list of the map between Vn to original V index.
)");
}



