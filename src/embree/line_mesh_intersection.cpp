#include "default_types.h"
#include <igl/embree/line_mesh_intersection.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto line_mesh_intersection(
    const nb::DRef<const Eigen::MatrixXN> &V_source,
    const nb::DRef<const Eigen::MatrixXN> &N_source,
    const nb::DRef<const Eigen::MatrixXN> &V_target,
    const nb::DRef<const Eigen::MatrixXI> &F_target)
  {
    // Explicit template instantiation: copies to col-major double/int
    Eigen::MatrixXd vs = V_source, ns = N_source, vt = V_target;
    Eigen::MatrixXi ft = F_target.cast<int>();
    Eigen::MatrixXd result =
      igl::embree::line_mesh_intersection<Eigen::MatrixXd, Eigen::MatrixXi>(
        vs, ns, vt, ft);
    return Eigen::MatrixXN(result);
  }
}

void bind_line_mesh_intersection(nb::module_ &m)
{
  m.def("line_mesh_intersection", &pyigl::line_mesh_intersection,
    "V_source"_a, "N_source"_a, "V_target"_a, "F_target"_a,
    R"(Project a point cloud onto a target mesh by ray casting along normals.

For each source point, a ray is cast along its normal (and the opposite
direction). The nearest intersection with the target mesh is returned as
barycentric coordinates.

@param[in] V_source  #V by 3 source point positions
@param[in] N_source  #V by 3 source point normals
@param[in] V_target  #V2 by 3 target mesh vertex positions
@param[in] F_target  #F2 by 3 target mesh triangle indices
@return  #V by 3 matrix of barycentric hits: each row is (face_id, b1, b2)
    where face_id is the index of the hit face and b1, b2 are barycentric
    coordinates w.r.t. the first two edges)");
}
