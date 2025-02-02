#include "default_types.h"
#include <igl/moments.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto moments(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Numeric m0;
    Eigen::VectorXN m1;
    Eigen::MatrixXN m2;
    igl::moments(V,F,m0,m1,m2);
    return std::make_tuple(m0,m1,m2);
  }

}

// Bind the wrapper to the Python module
void bind_moments(nb::module_ &m)
{
  m.def(
    "moments",
    &pyigl::moments, 
    "V"_a, 
    "F"_a,
R"(Computes the moments of mass for a solid object bound by a triangle mesh.

@param[in] V  #V by 3 list of rest domain positions
@param[in] F  #F by 3 list of triangle indices into V
@param[out] m0  zeroth moment of mass, total signed volume of solid.
@param[out] m1  first moment of mass, center of mass (centroid) times total mass
@param[out] m2  second moment of mass, moment of inertia with center of mass as reference point

\see centroid
)");
}
