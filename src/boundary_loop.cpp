#include "default_types.h"
#include <igl/boundary_loop.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for boundary_loop that returns all loops as a vector of vectors
  auto boundary_loop(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    std::vector<std::vector<Integer>> loops;
    igl::boundary_loop(F, loops);
    return loops;
  }
}

// Bind the wrapper to the Python module
void bind_boundary_loop(nb::module_ &m)
{
  m.def(
    "boundary_loop",
    &pyigl::boundary_loop,
    "F"_a,
R"(Compute all ordered boundary loops for a manifold mesh.

@param[in] F  #F by dim list of mesh faces
@return List of lists of boundary vertices, where each sublist represents a loop)");
}

