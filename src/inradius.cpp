#include "default_types.h"
#include <igl/inradius.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto inradius(
    const nb::DRef<const Eigen::MatrixXN> & V,
    const nb::DRef<const Eigen::MatrixXI> & F)
  {
    Eigen::VectorXN R;
    igl::inradius(V, F, R);
    return R;
  }
}

void bind_inradius(nb::module_ &m)
{
  m.def("inradius", &pyigl::inradius,
    "V"_a,
    "F"_a,
    R"(Compute the inradius of each triangle in a mesh (V,F)
@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by 3 list of triangle indices into V
@param[out] R  #F list of inradii)");
}
