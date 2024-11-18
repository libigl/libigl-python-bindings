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
  std::string matlab_format_dense(const nb::DRef<const Eigen::MatrixXN> &M, const std::string &name = "")
  {
    std::ostringstream oss;
    oss << igl::matlab_format(M, name);
    return oss.str();
  }

  std::string matlab_format_sparse(const Eigen::SparseMatrix<Numeric> &S, const std::string &name = "")
  {
    return igl::matlab_format(S, name);
  }

  std::string matlab_format_scalar(Numeric v, const std::string &name = "")
  {
    return igl::matlab_format(v, name);
  }

  std::string matlab_format_index(const nb::DRef<const Eigen::MatrixXI> &M, const std::string &name = "")
  {
    return igl::matlab_format_index(M, name);
  }
  
  std::string matlab_format_index_vector(const nb::DRef<const Eigen::VectorXI> &M, const std::string &name = "")
  {
    return igl::matlab_format_index(M, name);
  }

  std::string matlab_format_dense_vector(const nb::DRef<const Eigen::VectorXN> &M, const std::string &name = "")
  {
    std::ostringstream oss;
    oss << igl::matlab_format(M, name);
    return oss.str();
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
    &pyigl::matlab_format_dense_vector,
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

  m.def(
    "matlab_format_index",
    &pyigl::matlab_format_index_vector,
    "M"_a,
    "name"_a = "",
    R"(Format a matrix for MATLAB-style output with 1-based indexing.)");
}
