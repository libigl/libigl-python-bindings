#include "default_types.h"
#include <igl/readCSV.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto readCSV(const std::string &filename)
  {
    // igl::readCSV takes Eigen::Matrix<Scalar, Dynamic, Dynamic>& (ColMajor)
    Eigen::MatrixXd M;
    if (!igl::readCSV(filename, M))
      throw std::runtime_error("Failed to read CSV file: " + filename);
    return Eigen::MatrixXN(M);
  }
}

void bind_readCSV(nb::module_ &m)
{
  m.def("readCSV", &pyigl::readCSV, "filename"_a,
    R"(Read a matrix from a CSV file.

@param[in] filename  path to .csv file
@return M  matrix of values read from the CSV)");
}
