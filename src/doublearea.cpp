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
  nb::object doublearea(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXN> &A,
    const nb::DRef<const Eigen::MatrixXN> &B,
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::MatrixXN> &l,
    const Numeric nan_replacement)
  {
    Eigen::VectorXN dblA;
    if(l.size() > 0)
    {
      igl::doublearea(l, nan_replacement, dblA);
    }else
    {
      // if not isnan(nan_replacement) then throw error
      if(!std::isnan(nan_replacement))
      {
        throw std::invalid_argument("nan_replacement must be NaN if l is not provided");
      }
      if(A.size() > 0)
      {
        igl::doublearea(A, B, C, dblA);
      }
      else
      {
        igl::doublearea(V, F, dblA);
      }
    }
    return nb::cast(dblA);
  }
}

// Bind the wrapper to the Python module
void bind_doublearea(nb::module_ &m)
{
  m.def(
    "doublearea",
    &pyigl::doublearea,
    "V"_a=Eigen::MatrixXN(),
    "F"_a=Eigen::MatrixXI(),
    "A"_a=Eigen::MatrixXN(),
    "B"_a=Eigen::MatrixXN(),
    "C"_a=Eigen::MatrixXN(),
    "l"_a=Eigen::MatrixXN(),
    "nan_replacement"_a=std::numeric_limits<Numeric>::quiet_NaN(),
R"(Computes twice the area for each input triangle or quad.

@param[in] V  eigen matrix #V by 3
@param[in] F  #F by (3|4) list of mesh face indices into rows of V

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

@param[in] A #F by dim list of triangle corner positions
@param[in] B #F by dim list of triangle corner positions
@param[in] C #F by dim list of triangle corner positions

@param[out] dblA #F list of triangle double areas
  )"
    );
}

