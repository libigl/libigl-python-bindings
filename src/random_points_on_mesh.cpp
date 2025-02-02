#include "default_types.h"
#include <igl/random_points_on_mesh.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for vertex_components with face indices
  auto random_points_on_mesh(
    const Integer n,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXI FI;
    Eigen::MatrixXN B,X;
    igl::random_points_on_mesh(n, V, F,  B, FI, X);
    return std::make_tuple(B, FI, X);
  }
}

// Bind the wrappers to the Python module
void bind_random_points_on_mesh(nb::module_ &m)
{
  // Binding for vertex_components with adjacency matrix and counts
  m.def(
    "random_points_on_mesh",
    &pyigl::random_points_on_mesh,
    "n"_a,
    "V"_a,
    "F"_a,
    R"(
 Randomly sample a mesh (V,F) n times.

 @param[in] n  number of samples
 @param[in] V  #V by dim list of mesh vertex positions
 @param[in] F  #F by 3 list of mesh triangle indices
 @param[out] B  n by 3 list of barycentric coordinates, ith row are coordinates of
     ith sampled point in face FI(i)
 @param[in] urbg An instance of UnformRandomBitGenerator (e.g.,
  `std::minstd_rand(0)`)
 @param[out] FI  n list of indices into F 
 @param[in,out] urbg An instance of UnformRandomBitGenerator.
 @param[out] X  n by dim list of sample positions.)");
}

