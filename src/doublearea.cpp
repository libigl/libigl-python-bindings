#include "default_types.h"
#include <igl/doublearea.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <limits>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for doublearea function
  auto doublearea_VF(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXN dblA;
    igl::doublearea(V, F, dblA);
    return dblA;
  }
  auto doublearea_ABC(
    const nb::DRef<const Eigen::MatrixXN> &A,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXN> &C)
  {
    Eigen::VectorXN dblA;
    igl::doublearea(A, B, C, dblA);
    return dblA;
  }
  auto doublearea_l(
    const nb::DRef<const Eigen::MatrixXN> &l,
    const Numeric nan_replacement)
  {
    Eigen::VectorXN dblA;
    igl::doublearea(l, nan_replacement, dblA);
    return dblA;
  }
}

// Bind the wrapper to the Python module
void bind_doublearea(nb::module_ &m)
{
  m.def(
    "doublearea",
    &pyigl::doublearea_VF,
    "V"_a=Eigen::MatrixXN(),
    "F"_a=Eigen::MatrixXI(),
R"(Computes twice the area for each input triangle or quad.

@param[in] V  eigen matrix #V by 3
@param[in] F  #F by (3|4) list of mesh face indices into rows of V
@param[out] dblA #F list of triangle double areas
  )"
    );
  m.def(
    "doublearea",
    &pyigl::doublearea_ABC,
    "A"_a=Eigen::MatrixXN(),
    "B"_a=Eigen::MatrixXN(),
    "C"_a=Eigen::MatrixXN(),
R"(Computes twice the area for each input triangle or quad.

@param[in] A #F by dim list of triangle corner positions
@param[in] B #F by dim list of triangle corner positions
@param[in] C #F by dim list of triangle corner positions
@param[out] dblA #F list of triangle double areas
  )"
    );
  m.def(
    "doublearea",
    &pyigl::doublearea_l,
    "l"_a=Eigen::MatrixXN(),
    "nan_replacement"_a=std::numeric_limits<Numeric>::quiet_NaN(),
R"(Computes twice the area for each input triangle or quad.

@param[in] l  #F by dim list of edge lengths using for triangles, columns correspond to edges 23,31,12
@param[in] nan_replacement  what value should be used for triangles whose given
   edge lengths do not obey the triangle inequality. These may be very
   wrong (e.g., [100 1 1]) or may be nearly degenerate triangles whose
   floating point side length computation leads to breach of the triangle
   inequality. One may wish to set this parameter to 0 if side lengths l
   are _known_ to come from a valid embedding (e.g., some mesh (V,F)). In
   that case, the only circumstance the triangle inequality is broken is
   when the triangle is nearly degenerate and floating point error
   dominates: hence replacing with zero is reasonable.
@param[out] dblA #F list of triangle double areas
  )"
    );
}

