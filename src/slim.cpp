#include "default_types.h"
// Not templated at all
#include <igl/slim.h>
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
  auto slim_precompute(
    const Eigen::MatrixXd &V, // maybe copy here to avoid yet another copy in slim
    const Eigen::MatrixXi &F,
    const Eigen::MatrixXd &V_init,
    const igl::MappingEnergyType slim_energy,
    const Eigen::VectorXi &b,
    const Eigen::MatrixXd &bc,
    const double soft_p)
  {
    igl::SLIMData data;
    igl::slim_precompute(V, F, V_init, data, slim_energy, b, bc, soft_p);
    return data;
  }

  auto slim_solve(
    igl::SLIMData &data,
    int iter_num)
  {
    return igl::slim_solve(data, iter_num);
  }

}

// Bind the wrapper to the Python module
void bind_slim(nb::module_ &m)
{
  nb::class_<igl::SLIMData>(m, "SLIMData")
    .def(nb::init<const Eigen::MatrixXd &, const Eigen::MatrixXi &>());
  m.def(
    "slim_precompute",
    &pyigl::slim_precompute,
    "V"_a,
    "F"_a,
    "V_init"_a,
    "slim_energy"_a,
    "b"_a,
    "bc"_a,
    "soft_p"_a=1e5,
    R"(Precompute data for SLIM optimization.
    
    @param[in] V  #V by 3 list of mesh vertex positions
    @param[in] F  #F by (3|4) list of mesh elements (triangles or tetrahedra)
    @param[in] V_init  #V by 3 list of initial mesh vertex positions
    @param[in] slim_energy  Energy to minimize
    @param[in] b  list of boundary indices into V
    @param[in] bc  #b by 3 list of boundary conditions
    @param[in] soft_p  Soft penalty factor (can be zero)");
  m.def(
    "slim_solve",
    &pyigl::slim_solve,
    "data"_a,
    "iter_num"_a=1,
    R"(Run iterations of SLIM optimization.
    
    @param[in] data  Precomputation data structure
    @param[in] iter_num  Number of iterations to run
    @return #V by 3 list of mesh vertex positions)");
}





