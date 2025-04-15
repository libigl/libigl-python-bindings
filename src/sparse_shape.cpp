#include "default_types.h"
#include <nanobind/nanobind.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto sparse_shape( const Eigen::SparseMatrix<Integer> &A)
  {
    Eigen::Matrix<Integer,2,1> dims(A.rows(), A.cols());
    return dims;
  }
}

// Bind the wrapper to the Python module
void bind_sparse_shape(nb::module_ &m)
{
  m.def(
    "sparse_shape",
    &pyigl::sparse_shape,
    "A"_a,
R"("Returns shape of A as 2-vector)");
}


