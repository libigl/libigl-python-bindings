#include "default_types.h"
#include <igl/internal_angles.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto internal_angles(
      const nb::DRef<const Eigen::MatrixXN> &V,
      const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXN K;
    igl::internal_angles(V, F, K);
    return K;
  }
}

void bind_internal_angles(nb::module_ &m)
{
  m.def("internal_angles", &pyigl::internal_angles,
        "V"_a,
        "F"_a,
        R"(Compute internal angles for all tets of a given tet mesh (V,T).
@param[in] V  #V by dim eigen Matrix of mesh vertex nD positions
@param[in] F  #F by poly-size eigen Matrix of face (triangle) indices
@param[out] K  #F by poly-size eigen Matrix of internal angles
    for triangles, columns correspond to edges [1,2],[2,0],[0,1])");
}
