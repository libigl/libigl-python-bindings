#include "default_types.h"
#include <igl/extract_manifold_patches.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto extract_manifold_patches(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXI P;
    int n = igl::extract_manifold_patches(F, P);
    return std::make_tuple(n, Eigen::VectorXI(P));
  }
}

void bind_extract_manifold_patches(nb::module_ &m)
{
  m.def("extract_manifold_patches", &pyigl::extract_manifold_patches, "F"_a,
    R"(Extract maximal manifold patches from a triangle mesh.

A patch is a maximal subset of faces connected via manifold edges.

@param[in] F  #F by 3 list of triangle indices
@return n  number of manifold patches
@return P  #F list of patch indices for each face)");
}
