#include "default_types.h"
#include <igl/lbs_matrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto lbs_matrix(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXN> &W)
  {
    // igl::lbs_matrix takes Eigen::MatrixXd (ColMajor) — copy from RowMajor
    Eigen::MatrixXd v = V, w = W;
    Eigen::MatrixXd M;
    igl::lbs_matrix(v, w, M);
    return Eigen::MatrixXN(M);
  }
}

void bind_lbs_matrix(nb::module_ &m)
{
  m.def("lbs_matrix", &pyigl::lbs_matrix, "V"_a, "W"_a,
    R"(Construct the linear blend skinning matrix M.

V' = M * T where V' are deformed positions, M encodes rest positions and
weights, T is a stack of transposed transformation matrices.

@param[in] V  #V by dim list of rest vertex positions
@param[in] W  #V by #handles list of skinning weights
@return M  #V by #handles*(dim+1) linear blend skinning matrix)");
}
