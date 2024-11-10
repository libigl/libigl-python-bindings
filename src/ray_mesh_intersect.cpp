#include "default_types.h"
#include <igl/ray_mesh_intersect.h>
#include <igl/Hit.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for ray_mesh_intersect with overload handling
  std::vector<std::tuple<Integer,Numeric,Numeric,Numeric>>
    ray_mesh_intersect(
    const Eigen::VectorXN &source,
    const Eigen::VectorXN &dir,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const bool first = false)
  {
    std::vector<std::tuple<Integer,Numeric,Numeric,Numeric>> out;
    if (first)
    {
      // Overload for a single hit
      igl::Hit<Numeric> hit;
      bool result = igl::ray_mesh_intersect(source, dir, V, F, hit);
      out.emplace_back(hit.id, hit.t, hit.u, hit.v);
    }
    else
    {
      // Overload for all hits
      std::vector<igl::Hit<Numeric> > hits;
      bool result = igl::ray_mesh_intersect(source, dir, V, F, hits);
      for (const auto &hit : hits)
      {
        out.emplace_back(hit.id, hit.t, hit.u, hit.v);
      }
    }
    return out;
  }
}

// Bind the wrapper to the Python module
void bind_ray_mesh_intersect(nb::module_ &m)
{
  m.def(
    "ray_mesh_intersect",
    &pyigl::ray_mesh_intersect,
    "source"_a,
    "dir"_a,
    "V"_a,
    "F"_a,
    "first"_a = false,
R"(Shoot a ray against a mesh (V, F) and collect hits.

@param[in] source  3-vector origin of the ray
@param[in] dir     3-vector direction of the ray
@param[in] V       #V by 3 list of mesh vertex positions
@param[in] F       #F by 3 list of mesh face indices into V
@param[in] first If True, only return the first hit (if any)
@return Sorted list of hits if any exist, otherwise None)");
}
