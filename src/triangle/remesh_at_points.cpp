#include "default_types.h"
#include <igl/triangle/remesh_at_points.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for triangle::remesh_at_points function
  auto remesh_at_points(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::VectorXI> &FI)
  {
    Eigen::MatrixXN VV;
    Eigen::MatrixXI FF;
    Eigen::VectorXI J;
    Eigen::VectorXI K;
    igl::triangle::remesh_at_points(V, F, B, FI, VV, FF, J, K);
    return std::make_tuple(VV, FF, J, K);
  }
}

void bind_remesh_at_points(nb::module_ &m)
{
  m.def(
    "remesh_at_points",
    &pyigl::remesh_at_points,
    "V"_a,
    "F"_a,
    "B"_a,
    "FI"_a,
R"(Given a set of unique points on a mesh specified by barycentric coordinates
and a triangle index, remesh the mesh to include these points as vertices.
Barycentric coordinates should be non-negative and sum to 1. Vertex-points are
not inserted (but tracked in K). Edge-points are inserted and the edge is split
on all incident faces. Face-points are inserted. The output preserves the
(non-)manifoldness of the input. The input mesh can be in 3D (or any dimension).

@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by 3 list of triangle indices into rows of V
@param[in] B  #B by 3 list of barycentric coordinates, ith row are coordinates
              of ith sampled point in face FI(i)
@param[in] FI  #B list of indices into F
@param[out] VV  #VV by dim list of mesh vertex positions (top #V rows is always
                V; bottom rows are new vertices)
@param[out] FF  #FF by 3 list of triangle indices into rows of VV
@param[out] J  #FF list of indices into F
@param[out] K  #B list of indices into VV)");
}
