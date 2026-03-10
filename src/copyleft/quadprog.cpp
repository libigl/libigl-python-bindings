#include "default_types.h"
#include <igl/copyleft/quadprog.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto quadprog(
    const nb::DRef<const Eigen::MatrixXN> &G,
    const nb::DRef<const Eigen::VectorXN> &g0,
    const nb::DRef<const Eigen::MatrixXN> &CE,
    const nb::DRef<const Eigen::VectorXN> &ce0,
    const nb::DRef<const Eigen::MatrixXN> &CI,
    const nb::DRef<const Eigen::VectorXN> &ci0)
  {
    // quadprog uses non-template MatrixXd (col-major); copy from row-major inputs
    Eigen::MatrixXd G_d = G, CE_d = CE, CI_d = CI;
    Eigen::VectorXd g0_d = g0, ce0_d = ce0, ci0_d = ci0;
    Eigen::VectorXd x;
    if(!igl::copyleft::quadprog(G_d, g0_d, CE_d, ce0_d, CI_d, ci0_d, x))
      throw std::runtime_error("quadprog: solver failed");
    return Eigen::VectorXN(x);
  }
}

void bind_quadprog(nb::module_ &m)
{
  m.def("quadprog", &pyigl::quadprog,
    "G"_a, "g0"_a,
    "CE"_a = Eigen::MatrixXN(), "ce0"_a = Eigen::VectorXN(),
    "CI"_a = Eigen::MatrixXN(), "ci0"_a = Eigen::VectorXN(),
    R"(Solve a dense convex quadratic program.

Minimizes:  0.5 x' G x + g0' x
Subject to: CE' x + ce0  = 0
            CI' x + ci0 >= 0

@param[in] G    #x by #x positive semi-definite quadratic cost matrix
@param[in] g0   #x linear cost vector
@param[in] CE   #x by #ce equality constraint matrix (optional)
@param[in] ce0  #ce equality constraint rhs (optional)
@param[in] CI   #x by #ci inequality constraint matrix (optional)
@param[in] ci0  #ci inequality constraint rhs (optional)
@return x  #x solution vector
@raises RuntimeError if the solver fails)");
}
