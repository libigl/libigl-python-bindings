#include "default_types.h"
#include <igl/embree/reorient_facets_raycast.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto reorient_facets_raycast(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const int rays_total_,
    const int rays_minimum,
    const bool facet_wise,
    const bool use_parity,
    const bool is_verbose)
  {
    const int rays_total = rays_total_==-1?F.rows()*100:rays_total_;
    Eigen::VectorXB I;
    Eigen::VectorXI C;
    igl::embree::reorient_facets_raycast(
      V,F,rays_total,rays_minimum,facet_wise,use_parity,is_verbose,I,C);
    return std::make_tuple(I,C);
  }
}

// Bind the wrapper to the Python module
void bind_reorient_facets_raycast(nb::module_ &m)
{
  m.def(
    "reorient_facets_raycast",
    &pyigl::reorient_facets_raycast, 
    "V"_a, 
    "F"_a,
    "rays_total"_a=-1,
    "rays_minimum"_a=10,
    "facet_wise"_a=false,
    "use_parity"_a=false,
    "is_verbose"_a=false,
R"(Orient each component (identified by C) of a mesh (V,F) using ambient
occlusion such that the front side is less occluded than back side, as
described in "A Simple Method for Correcting Facet Orientations in
Polygon Meshes Based on Ray Casting" [Takayama et al. 2014].

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@param[in] rays_total  Total number of rays that will be shot
@param[in] rays_minimum  Minimum number of rays that each patch should receive
@param[in] facet_wise  Decision made for each face independently, no use of patches
    (i.e., each face is treated as a patch)
@param[in] use_parity  Use parity mode
@param[in] is_verbose  Verbose output to cout
@param[out] I  #F list of whether face has been flipped
@param[out] C  #F list of patch ID (output of bfs_orient > manifold patches)
)");
}
