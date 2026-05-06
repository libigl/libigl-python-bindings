#include "default_types.h"
#include <igl/pseudonormal_test.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto pseudonormal_test(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &FN,
    const nb::DRef<const Eigen::MatrixXN> &VN,
    const nb::DRef<const Eigen::MatrixXN> &EN,
    const nb::DRef<const Eigen::MatrixXI> &EMAP,
    const nb::DRef<const Eigen::MatrixXN> &q,
    const nb::DRef<const Eigen::MatrixXN> &c_in,
    const int f)
  {
    // EMAP uses single-index access — needs VectorXI
    const Eigen::VectorXI emap = EMAP.reshaped();
    // q and c used as row vectors (operations with V.row(), FN.row(), etc.)
    // Use RowVectorXd (1×Dynamic) so product = Dynamic ✓ and row-vector arithmetic works
    const Eigen::RowVectorXd q_v = Eigen::VectorXd(q.reshaped()).transpose();
    Eigen::RowVectorXd c_v = Eigen::VectorXd(c_in.reshaped()).transpose();
    Eigen::RowVectorXd n;
    Numeric s;
    igl::pseudonormal_test(V, F, FN, VN, EN, emap, q_v, f, c_v, s, n);
    return std::make_tuple(s, Eigen::MatrixXN(n));
  }
}

void bind_pseudonormal_test(nb::module_ &m)
{
  m.def("pseudonormal_test", &pyigl::pseudonormal_test,
    "V"_a, "F"_a, "FN"_a, "VN"_a, "EN"_a, "EMAP"_a, "q"_a, "c"_a, "f"_a,
    R"(Determine the sign of a query point w.r.t. a mesh using the pseudonormal.

Given a mesh (V,F), a query point q, a precomputed closest point c on face f,
determine whether q is inside (s=-1) or outside (s=+1) the mesh.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] FN  #F by 3 list of face normals
@param[in] VN  #V by 3 list of vertex normals (angle weighted)
@param[in] EN  #E by 3 list of edge normals (uniform weighted)
@param[in] EMAP  #F*3 mapping from face-edges to E
@param[in] q  3-vector query point
@param[in] c  3-vector closest point on mesh (precomputed)
@param[in] f  index of closest face in F
@return s  sign: -1 if inside, +1 if outside
@return n  3-vector normal at closest point)");
}
