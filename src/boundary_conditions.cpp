#include "default_types.h"
#include <igl/boundary_conditions.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto boundary_conditions(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::VectorXI> &P,
    const nb::DRef<const Eigen::MatrixXI> &BE,
    const nb::DRef<const Eigen::MatrixXI> &CE,
    const nb::DRef<const Eigen::MatrixXI> &CF)
  {

    Eigen::VectorXI b;
    Eigen::MatrixXN bc;
    igl::boundary_conditions(V, Ele, C, P, BE, CE, CF, b, bc);
    return std::make_tuple(b, bc);
  }
}

void bind_boundary_conditions(nb::module_ &m)
{
  m.def(
    "boundary_conditions", 
    &pyigl::boundary_conditions,
    "V"_a,
    "Ele"_a,
    "C"_a,
    "P"_a=Eigen::VectorXI(),
    "BE"_a=Eigen::MatrixXI(),
    "CE"_a=Eigen::MatrixXI(),
    "CF"_a=Eigen::MatrixXI(),
    R"(
Compute boundary conditions for automatic weights computation. WIP)");
}
