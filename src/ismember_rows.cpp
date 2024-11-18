#include "default_types.h"
#include <igl/ismember_rows.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for ismember_rows with simplicial mesh (F)
  auto ismember_rows(
    const nb::DRef<const Eigen::MatrixXI> &A,
    const nb::DRef<const Eigen::MatrixXI> &B)
  {
    Eigen::Array<bool,Eigen::Dynamic,1> IA;
    Eigen::VectorXI LOCB;
    igl::ismember_rows(A,B,IA,LOCB);
    return std::make_tuple(IA,LOCB);
  }

}

// Bind the wrapper to the Python module
void bind_ismember_rows(nb::module_ &m)
{
  m.def(
    "ismember_rows",
    &pyigl::ismember_rows,
    "A"_a,
    "B"_a,
R"(
Determine if row of A exist in rows of B

@param[in] A  ma by na matrix of Integers
@param[in] B  mb by nb matrix of Integers
@param[out] IA  ma by 1 lest of flags whether corresponding element of A
  exists in B
@param[out] LOCB  ma by 1 list matrix of indices in B locating matching
  element (-1 if not found), indices assume column major ordering
)");
}

