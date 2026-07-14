#include "default_types.h"
#include <igl/predicates/delaunay_triangulation.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  Eigen::MatrixXi delaunay_triangulation(
    const Eigen::MatrixXN &V)
  {
    Eigen::MatrixXi F;
    igl::predicates::delaunay_triangulation(V, F);
    return F;
  }
}

void bind_delaunay_triangulation(nb::module_ &m)
{
  m.def(
    "delaunay_triangulation",
    &pyigl::delaunay_triangulation,
    "V"_a,
R"(Compute a Delaunay triangulation of a 2D point set using exact predicates.

@param[in] V  #V by 2 list of 2D vertex positions
@return F  #F by 3 list of triangle indices into V.)");
}
