#include "default_types.h"
#include <igl/bfs_orient.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto bfs_orient( 
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI FF;
    Eigen::VectorXI C;
    igl::bfs_orient(F,FF,C);
    return std::make_tuple(FF,C);
  }
}

// Bind the wrapper to the Python module
void bind_bfs_orient(nb::module_ &m)
{
  m.def(
    "bfs_orient",
    &pyigl::bfs_orient,
    "F"_a,
    R"(
Consistently orient faces in orientable patches using BFS.

@param[in] F  #F by 3 list of faces
@param[out] FF  #F by 3 list of faces (OK if same as F)
@param[out] C  #F list of component ids)"
  );
}

