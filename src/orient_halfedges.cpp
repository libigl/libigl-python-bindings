#include "default_types.h"
#include <igl/orient_halfedges.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto orient_halfedges(
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI E,oE;
    igl::orient_halfedges(F,E,oE);
    return std::make_tuple(E,oE);
  }
}

// Bind the wrapper to the Python module
void bind_orient_halfedges(nb::module_ &m)
{
  m.def(
    "orient_halfedges",
    &pyigl::orient_halfedges, 
    "F"_a, 
R"(Orients halfedges for a triangle mesh, assigning them to a unique edge.
  
@param[in] F #F by 3 input mesh connectivity
@param[out] E  #F by 3 a mapping from each halfedge to each edge
@param[out] oE #F by 3 the orientation (e.g., -1 or 1) of each halfedge compared to
  the orientation of the actual edge. Every edge appears positively oriented
  exactly once.

\see unique_simplices)"
    );
}


