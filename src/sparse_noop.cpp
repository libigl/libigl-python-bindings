#include "default_types.h"
#include <nanobind/nanobind.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto sparse_noop( const Eigen::SparseMatrix<Integer> &A)
  {
    return A;
  }
}

// Bind the wrapper to the Python module
void bind_sparse_noop(nb::module_ &m)
{
  m.def(
    "sparse_noop",
    &pyigl::sparse_noop,
    "A"_a,
R"("Returns input A)");
}

