#include "default_types.h"
#include <igl/bijective_composite_harmonic_mapping.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto bijective_composite_harmonic_mapping(
    const nb::DRef<const Eigen::MatrixXN> & V,
    const nb::DRef<const Eigen::MatrixXI> & F,
    const nb::DRef<const Eigen::VectorXI> & b,
    const nb::DRef<const Eigen::MatrixXN> & bc,
    const int min_steps,
    const int max_steps,
    const int num_inner_iters,
    const bool test_for_flips)
  {
    Eigen::MatrixXN U;
    if(!igl::bijective_composite_harmonic_mapping(V, F, b, bc, min_steps, max_steps, num_inner_iters, test_for_flips, U))
    {
      throw std::runtime_error("bijective_composite_harmonic_mapping failed");
    }
    return U;
  }
}

void bind_bijective_composite_harmonic_mapping(nb::module_ &m)
{
  m.def("bijective_composite_harmonic_mapping", &pyigl::bijective_composite_harmonic_mapping,
    "V"_a,
    "F"_a,
    "b"_a,
    "bc"_a,
    "min_steps"_a=1,
    "max_steps"_a=200,
    "num_inner_iters"_a=20,
    "test_for_flips"_a=true,
    R"(Compute a injective planar mapping of a triangulated polygon (V,F) subjected to
boundary conditions (b,bc). The mapping should be bijective in the sense
that no triangles' areas become negative (this assumes they started
positive). This mapping is computed by "composing" harmonic mappings
between incremental morphs of the boundary conditions. This is a bit like
a discrete version of "Bijective Composite Mean Value Mappings" [Schneider
et al. 2013] but with a discrete harmonic map (cf. harmonic coordinates)
instead of mean value coordinates. This is inspired by "Embedding a
triangular graph within a given boundary" [Xu et al. 2011].
@param[in] V  #V by 2 list of triangle mesh vertex positions
@param[in] F  #F by 3 list of triangle indices into V
@param[in] b  #b list of boundary indices into V
@param[in] bc  #b by 2 list of boundary conditions corresponding to b
@param[in] min_steps  minimum number of steps to take from V(b,:) to bc
@param[in] max_steps  minimum number of steps to take from V(b,:) to bc (if
   max_steps == min_steps then no further number of steps will be tried)
@param[in] num_inner_iters  number of iterations of harmonic solves to run after
   for each morph step (to try to push flips back in)
@param[in] test_for_flips  whether to check if flips occurred (and trigger more
   steps). if test_for_flips = false then this function always returns
   true
@param[out] U  #V by 2 list of output mesh vertex locations
@return true if and only if U contains a successful bijectie mapping)");
}
