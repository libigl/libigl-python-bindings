#include "default_types.h"
#include <igl/copyleft/cgal/coplanar.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  bool coplanar(const nb::DRef<const Eigen::MatrixXN> &V)
  {
    return igl::copyleft::cgal::coplanar(V);
  }
}

void bind_coplanar(nb::module_ &m)
{
  m.def("coplanar", &pyigl::coplanar, "V"_a,
    R"(Test whether all points lie on the same plane.

@param[in] V  #V by 3 list of 3D vertex positions
@return true if all points are coplanar)");
}
