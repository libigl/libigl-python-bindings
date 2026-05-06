#include "default_types.h"
#include <igl/per_vertex_attribute_smoothing.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto per_vertex_attribute_smoothing(
    const nb::DRef<const Eigen::MatrixXN> &Ain,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    // Aout must be same DerivedV as Ain — copy Ain to MatrixXN so both are plain types
    Eigen::MatrixXN ain = Ain, Aout;
    igl::per_vertex_attribute_smoothing(ain, F, Aout);
    return Aout;
  }
}

void bind_per_vertex_attribute_smoothing(nb::module_ &m)
{
  m.def("per_vertex_attribute_smoothing",
    &pyigl::per_vertex_attribute_smoothing,
    "Ain"_a, "F"_a,
    R"(Smooth vertex attributes using uniform Laplacian averaging.

@param[in] Ain  #V by #A matrix of vertex attributes
@param[in] F    #F by 3 list of triangle indices
@return Aout  #V by #A smoothed vertex attributes)");
}
