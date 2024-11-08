#include "default_types.h"
#include <igl/matlab_format.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/string.h>
#include <string>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for dense matrix formatting
  std::string matlab_format_dense(const nb::DRef<const Eigen::MatrixXN> &M, const std::string &name = "")
  {
    std::ostringstream oss;
    oss << igl::matlab_format(M, name);
    return oss.str();
  }

  // Wrapper for sparse matrix formatting
  std::string matlab_format_sparse(const Eigen::SparseMatrix<Numeric> &S, const std::string &name = "")
  {
    return igl::matlab_format(S, name);
  }

  // Wrapper for scalar formatting
  std::string matlab_format_scalar(Numeric v, const std::string &name = "")
  {
    return igl::matlab_format(v, name);
  }

  // Wrapper for matlab_format_index
  std::string matlab_format_index(const nb::DRef<const Eigen::MatrixXI> &M, const std::string &name = "")
  {
    return igl::matlab_format_index(M, name);
  }
}

// Bind the wrapper to the Python module
void bind_matlab_format(nb::module_ &m)
{
  m.def(
    "matlab_format",
    &pyigl::matlab_format_dense,
    "M"_a,
    "name"_a = "",
    R"(Format a dense matrix for MATLAB-style output.)");

  m.def(
    "matlab_format",
    &pyigl::matlab_format_sparse,
    "S"_a,
    "name"_a = "",
    R"(Format a sparse matrix for MATLAB-style output in IJV format.)");

  m.def(
    "matlab_format",
    nb::overload_cast<double, const std::string&>(&pyigl::matlab_format_scalar),
    "v"_a,
    "name"_a = "",
    R"(Format a double scalar for MATLAB-style output.)");

  m.def(
    "matlab_format_index",
    &pyigl::matlab_format_index,
    "M"_a,
    "name"_a = "",
    R"(Format a matrix for MATLAB-style output with 1-based indexing.)");
}
