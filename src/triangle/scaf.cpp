#include "default_types.h"
// Not templated at all
#include <igl/triangle/scaf.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto scaf_precompute(
    const Eigen::MatrixXd &V, // maybe copy here to avoid yet another copy in scaf
    const Eigen::MatrixXi &F,
    const Eigen::MatrixXd &V_init,
    const igl::MappingEnergyType scaf_energy,
    const Eigen::VectorXi &b,
    const Eigen::MatrixXd &bc,
    const double soft_p,
    igl::triangle::SCAFData & data)
  {
    igl::triangle::scaf_precompute(V, F, V_init, scaf_energy, b, bc, soft_p, data);
  }
  auto scaf_solve(
    const int iter_num,
    igl::triangle::SCAFData &data)
  {
    return igl::triangle::scaf_solve(iter_num, data);
  }
  auto scaf_system( igl::triangle::SCAFData &s)
  {
    Eigen::SparseMatrix<double> L;
    Eigen::VectorXd rhs;
    igl::triangle::scaf_system(s, L, rhs);
    return std::make_tuple(L, rhs);
  }

}

// Bind the wrapper to the Python module
void bind_scaf(nb::module_ &m)
{
  nb::class_<igl::triangle::SCAFData>(m, "SCAFData")
    .def(nb::init<>());
  m.def(
    "scaf_precompute",
    &pyigl::scaf_precompute,
    "V"_a,
    "F"_a,
    "V_init"_a,
    "scaf_energy"_a,
    "b"_a,
    "bc"_a,
    "soft_p"_a,
    "data"_a,
    R"(Compute necessary information to start using SCAF

@param[in] V           #V by 3 list of mesh vertex positions
@param[in] F           #F by 3/3 list of mesh faces (triangles/tets)
@param[in] V_init      #V by 3 list of initial mesh vertex positions
@param[in,out] data  resulting precomputed data
@param[in] slim_energy Energy type to minimize
@param[in] b           list of boundary indices into V (soft constraint)
@param[in] bc          #b by dim list of boundary conditions (soft constraint)
@param[in] soft_p      Soft penalty factor (can be zero)
)");
  m.def(
    "scaf_solve",
    &pyigl::scaf_solve,
    "iter_num"_a,
    "data"_a,
    R"(Run iter_num iterations of SCAF, with precomputed data
@param[in] data  precomputed data
@param[in] iter_num  number of iterations to run
@returns resulting V_o (in SLIMData): #V by dim list of mesh vertex positions
    )");
  m.def(
    "scaf_system",
    &pyigl::scaf_system,
    "s"_a,
    R"(Set up the SCAF system L * uv = rhs, without solving it.
@param[in] s:   igl::SCAFData. Will be modified by energy and Jacobian computation.
@param[out] L:   m by m matrix
@param[out] rhs: m by 1 vector
with m = dim * (#V_mesh + #V_scaf - #V_frame)
    )");


}






