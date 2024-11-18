#include "default_types.h"
// Not templated at all
#include <igl/arap.h>
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
  auto arap_precomputation(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const int dim,
    // Will be cast to int32_t in arap, so avoid potential double copy if passed
    // as int32_t
    const nb::DRef<const Eigen::VectorXi> &b, 
    igl::ARAPData &data)
  {
    if(!igl::arap_precomputation(V,F,dim,b,data))
    {
      throw std::runtime_error("arap_precomputation failed");
    }
  }

  auto arap_solve(
    const nb::DRef<const Eigen::MatrixXN> & bc, 
    igl::ARAPData &data,
    const nb::DRef<const Eigen::MatrixXN> & U0)
  {
    // igl::arap_solve expects U to be both the initial guess and the output 
    // not sure how to avoid this copy
    Eigen::MatrixXN U = U0;
    if(!igl::arap_solve(bc,data,U))
    {
      throw std::runtime_error("arap_solve failed");
    }
    return U;
  }

}

// Bind the wrapper to the Python module
void bind_arap(nb::module_ &m)
{
  nb::enum_<igl::ARAPEnergyType>(m, "ARAPEnergyType")
    .value("ARAP_ENERGY_TYPE_DEFAULT", igl::ARAPEnergyType::ARAP_ENERGY_TYPE_DEFAULT)
    .value("ARAP_ENERGY_TYPE_SPOKES", igl::ARAPEnergyType::ARAP_ENERGY_TYPE_SPOKES)
    .value("ARAP_ENERGY_TYPE_SPOKES_AND_RIMS", igl::ARAPEnergyType::ARAP_ENERGY_TYPE_SPOKES_AND_RIMS)
    .value("ARAP_ENERGY_TYPE_ELEMENTS", igl::ARAPEnergyType::ARAP_ENERGY_TYPE_ELEMENTS)
    .value("NUM_ARAP_ENERGY_TYPES", igl::ARAPEnergyType::NUM_ARAP_ENERGY_TYPES)
    .export_values()
    ;
  nb::class_<igl::ARAPData>(m, "ARAPData")
    .def(nb::init<>())
    .def_ro("n", &igl::ARAPData::n)
    .def_rw("G", &igl::ARAPData::G)
    .def_rw("energy", &igl::ARAPData::energy)
    .def_rw("with_dynamics", &igl::ARAPData::with_dynamics)
    .def_rw("f_ext", &igl::ARAPData::f_ext)
    .def_rw("vel", &igl::ARAPData::vel)
    .def_rw("h", &igl::ARAPData::h)
    .def_rw("ym", &igl::ARAPData::ym)
    .def_rw("max_iter", &igl::ARAPData::max_iter)
    ;
     
  m.def(
    "arap_precomputation",
    &pyigl::arap_precomputation,
    "V"_a,
    "F"_a,
    "dim"_a,
    "b"_a,
    "data"_a,
    R"()");
  m.def(
    "arap_solve",
    &pyigl::arap_solve,
    "bc"_a,
    "data"_a,
    "U"_a,
    R"()");
}





