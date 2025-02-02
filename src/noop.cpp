#include "default_types.h"
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;


namespace pyigl
{
  auto noop(
    const nb::DRef<const Eigen::MatrixXN> &N,
    const nb::DRef<const Eigen::MatrixXI> &I,
    const Eigen::SparseMatrixN &SN,
    const Eigen::SparseMatrixI &SI)
  {
    return nb::none();
  }
}

// Bind the wrapper to the Python module
void bind_noop(nb::module_ &m)
{
  m.def(
    "noop",
    &pyigl::noop, 
    "N"_a=Eigen::MatrixXN(),
    "I"_a=Eigen::MatrixXI(),
    "SN"_a=Eigen::SparseMatrixN(),
    "SI"_a=Eigen::SparseMatrixI(),
R"(Dummy function that does nothing. Useful for timing bindings overhead.)"
    );
}


