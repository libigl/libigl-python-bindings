#include "default_types.h"
#include <igl/polygons_to_triangles.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto polygons_to_triangles(
      const nb::DRef<const Eigen::VectorXI> &I,
      const nb::DRef<const Eigen::VectorXI> &C)
  {
    Eigen::MatrixXI F;
    Eigen::VectorXI J;
    igl::polygons_to_triangles(I,C,F,J);
    return std::make_tuple(F,J);
  }

}

// Bind the wrapper to the Python module
void bind_polygons_to_triangles(nb::module_ &m)
{
  m.def(
    "polygons_to_triangles",
    &pyigl::polygons_to_triangles, 
    "I"_a, 
    "C"_a, 
R"(Given a polygon mesh, trivially triangulate each polygon with a fan. This
purely combinatorial triangulation will work well for convex/flat polygons
and degrade otherwise.

@param[in] I  #I vectorized list of polygon corner indices into rows of some matrix V
@param[in] C  #polygons+1 list of cumulative polygon sizes so that C(i+1)-C(i) =
    size of the ith polygon, and so I(C(i)) through I(C(i+1)-1) are the
    indices of the ith polygon
@param[out] F  #F by 3 list of triangle indices into rows of V
@param[out] J  #F list of indices into 0:#P-1 of corresponding polygon

)");
}




