#include "default_types.h"
#include <igl/signed_distance.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>
#include <limits>
#include <stdexcept>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  template <typename Scalar>
  using MatrixXS = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, Options>;

  template <typename Scalar>
  auto signed_distance(
    const nb::DRef<const MatrixXS<Scalar>> &P,
    const nb::DRef<const MatrixXS<Scalar>> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const igl::SignedDistanceType sign_type,
    const Scalar lower_bound,
    const Scalar upper_bound)
  {
    Eigen::Matrix<Scalar, Eigen::Dynamic, 1> S;
    Eigen::VectorXI I;
    MatrixXS<Scalar> C,N;
    igl::signed_distance(P, V, F, sign_type, lower_bound, upper_bound, S, I, C, N);
    return std::make_tuple(S, I, C, N);
  }
}

void bind_signed_distance(nb::module_ &m)
{
  nb::enum_<igl::SignedDistanceType>(m, "SignedDistanceType")
    .value("SIGNED_DISTANCE_TYPE_PSEUDONORMAL", igl::SIGNED_DISTANCE_TYPE_PSEUDONORMAL)
    .value("SIGNED_DISTANCE_TYPE_WINDING_NUMBER", igl::SIGNED_DISTANCE_TYPE_WINDING_NUMBER)
    .value("SIGNED_DISTANCE_TYPE_UNSIGNED", igl::SIGNED_DISTANCE_TYPE_UNSIGNED)
    .value("SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER", igl::SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER)
    .value("SIGNED_DISTANCE_TYPE_DEFAULT", igl::SIGNED_DISTANCE_TYPE_DEFAULT)
    .export_values()
    ;
  const auto bind = [&m](auto scalar, bool convert)
  {
    using Scalar = decltype(scalar);
    m.def(
      "signed_distance",
      &pyigl::signed_distance<Scalar>,
      "P"_a.noconvert(!convert),
      "V"_a.noconvert(!convert),
      "F"_a,
      "sign_type"_a = igl::SIGNED_DISTANCE_TYPE_DEFAULT,
      "lower_bound"_a = -std::numeric_limits<Scalar>::infinity(),
      "upper_bound"_a = std::numeric_limits<Scalar>::infinity(),
R"(Computes signed distance to a mesh.

When P and V are both float32 arrays, use single precision and return float32
S, C, and N. Otherwise use the default double-precision conversion, including
mixed float32/float64 inputs. F is converted to int64 as needed.
The fast-winding-number method internally uses single precision in either case.

@param[in] P  #P by (2|3) list of query point positions
@param[in] V  #V by (2|3) list of vertex positions
@param[in] F  #F by ss list of triangle indices
@param[in] sign_type  method for computing distance sign: "pseudonormal", "winding_number", "unsigned", "fast_winding_number", or "default"
@param[in] lower_bound  lower bound of distances needed (default: -inf)
@param[in] upper_bound  upper bound of distances needed (default: inf)
@return Tuple containing:
  - S: #P list of smallest signed distances
  - I: #P list of facet indices corresponding to smallest distances
  - C: #P by (2|3) list of closest points
  - N: #P by (2|3) list of closest normals (empty unless sign_type="pseudonormal"))");
  };
  // Try the non-converting float overload first, including when F needs an
  // integer conversion in nanobind's second overload-resolution pass.
  bind(float(0), false);
  bind(Numeric(0), true);
}
