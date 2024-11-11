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
  auto signed_distance_type_from_string(const std::string & sign_type_str)
  {
    igl::SignedDistanceType sign_type;
    if (sign_type_str == "pseudonormal")
    {
      sign_type = igl::SIGNED_DISTANCE_TYPE_PSEUDONORMAL;
    }
    else if (sign_type_str == "winding_number")
    {
      sign_type = igl::SIGNED_DISTANCE_TYPE_WINDING_NUMBER;
    }
    else if (sign_type_str == "unsigned")
    {
      sign_type = igl::SIGNED_DISTANCE_TYPE_UNSIGNED;
    }
    else if (sign_type_str == "fast_winding_number")
    {
      sign_type = igl::SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER;
    }
    else if (sign_type_str == "default")
    {
      sign_type = igl::SIGNED_DISTANCE_TYPE_DEFAULT;
    }
    else
    {
      throw std::invalid_argument("Invalid sign_type: " + sign_type_str);
    }
    return sign_type;
  };

  auto signed_distance(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const std::string &sign_type_str,
    const Numeric lower_bound = -std::numeric_limits<Numeric>::infinity(),
    const Numeric upper_bound = std::numeric_limits<Numeric>::infinity())
  {
    const auto sign_type = signed_distance_type_from_string(sign_type_str);
    Eigen::VectorXN S;
    Eigen::VectorXI I;
    Eigen::MatrixXN C,N;
    igl::signed_distance(P, V, F, sign_type, lower_bound, upper_bound, S, I, C, N);
    return std::make_tuple(S, I, C, N);
  }
}

void bind_signed_distance(nb::module_ &m)
{
  m.def(
    "signed_distance",
    &pyigl::signed_distance,
    "P"_a,
    "V"_a,
    "F"_a,
    "sign_type"_a = "default",
    "lower_bound"_a = -std::numeric_limits<Numeric>::infinity(),
    "upper_bound"_a = std::numeric_limits<Numeric>::infinity(),
R"(Computes signed distance to a mesh.

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
}
