#include "default_types.h"
#include <igl/flipped_triangles.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto flipped_triangles(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXI X;
    igl::flipped_triangles(V, F, X);
    return X;
  }
}

void bind_flipped_triangles(nb::module_ &m)
{
  m.def("flipped_triangles", &pyigl::flipped_triangles, "V"_a, "F"_a,
    R"(Find indices of flipped triangles in a 2D UV mapping.

@param[in] V  #V by 2 list of UV vertex positions
@param[in] F  #F by 3 list of triangle indices
@return X  list of indices into F of flipped triangles)");
}
