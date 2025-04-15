#include "default_types.h"
#include <nanobind/nanobind.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto sparse_map_noop( const Eigen::Map<const Eigen::SparseMatrix<Integer>> &A)
  {
    return A;
  }
}

// Bind the wrapper to the Python module
void bind_sparse_map_noop(nb::module_ &m)
{
  m.def(
    "sparse_map_noop",
    &pyigl::sparse_map_noop,
    "A"_a,
R"("Returns input A)");
}

