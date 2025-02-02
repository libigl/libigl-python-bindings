#include "default_types.h"
#include <igl/point_mesh_squared_distance.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for point_mesh_squared_distance function
  auto point_mesh_squared_distance(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele)
  {
    Eigen::VectorXN sqrD;
    Eigen::VectorXI I;
    Eigen::MatrixXN C;
    igl::point_mesh_squared_distance(P, V, Ele, sqrD, I, C);
    return std::make_tuple(sqrD, I, C);
  }
}

// Bind the wrapper to the Python module
void bind_point_mesh_squared_distance(nb::module_ &m)
{
  m.def(
    "point_mesh_squared_distance",
    &pyigl::point_mesh_squared_distance,
    "P"_a,
    "V"_a,
    "Ele"_a,
R"(Compute distances from a set of points P to a triangle mesh (V,F)

@param[in] P  #P by 3 list of query point positions
@param[in] V  #V by 3 list of vertex positions
@param[in] Ele  #Ele by (3|2|1) list of (triangle|edge|point) indices
@param[out] sqrD  #P list of smallest squared distances
@param[out] I  #P list of primitive indices corresponding to smallest distances
@param[out] C  #P by 3 list of closest points

\bug This only computes distances to given primitives. So
unreferenced vertices are ignored. However, degenerate primitives are
handled correctly: triangle [1 2 2] is treated as a segment [1 2], and
triangle [1 1 1] is treated as a point. So one _could_ add extra
combinatorially degenerate rows to Ele for all unreferenced vertices to
also get distances to points.
)");
}

