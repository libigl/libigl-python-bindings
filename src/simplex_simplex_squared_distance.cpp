#include "default_types.h"
#include <igl/simplex_simplex_squared_distance.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for simplex_simplex_squared_distance function
  auto simplex_simplex_squared_distance(
    const nb::DRef<const Eigen::MatrixXN> &V1,
    const nb::DRef<const Eigen::MatrixXN> &V2)
  {
    Numeric sqrdDist;
    Eigen::VectorXN B1;
    Eigen::VectorXN B2;
    igl::simplex_simplex_squared_distance(V1, V2, sqrdDist, B1, B2);
    return std::make_tuple(sqrdDist, B1, B2);
  }
}

// Bind the wrapper to the Python module
void bind_simplex_simplex_squared_distance(nb::module_ &m)
{
  m.def(
    "simplex_simplex_squared_distance",
    &pyigl::simplex_simplex_squared_distance,
    "V1"_a,
    "V2"_a,
R"(Find the squared distance between closest points on simplices with corners
V1 and V2, respectively. V1 and V2 don't have to be the same simplex size,
but they must have the same number of columns (dimension). This function
works recursively.

@param[in] V1  #V1 by dim list of simplex corners
@param[in] V2  #V2 by dim list of simplex corners
@param[out] sqrdDist  squared distance between closest points on simplices
@param[out] B1  #V1 list of barycentric coordinates of closest point on simplex 1
@param[out] B2  #V2 list of barycentric coordinates of closest point on simplex 2)");
}
