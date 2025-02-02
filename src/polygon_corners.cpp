#include "default_types.h"
#include <igl/polygon_corners.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto polygon_corners(const std::vector<std::vector<Integer> > & P)
  {
    Eigen::VectorXI I, C;
    igl::polygon_corners(P,I,C);
    return std::make_tuple(I,C);
  }

  auto polygon_corners_kgon(
    const nb::DRef<const Eigen::MatrixXI> &Q)
  {
    Eigen::VectorXI I, C;
    igl::polygon_corners(Q,I,C);
    return std::make_tuple(I,C);
  }
}

// Bind the wrapper to the Python module
void bind_polygon_corners(nb::module_ &m)
{
  m.def(
    "polygon_corners",
    &pyigl::polygon_corners, 
    "P"_a, 
R"(Convert a list-of-lists polygon mesh faces representation to list of
polygon corners and sizes

@param[in] P  #P list of lists of vertex indices into rows of some matrix V
@param[out] I  #I vectorized list of polygon corner indices into rows of some matrix V
@param[out] C  #P+1 list of cumulative polygon sizes so that C(i+1)-C(i) = size of
    the ith polygon, and so I(C(i)) through I(C(i+1)-1) are the indices of
    the ith polygon

)");
  m.def(
    "polygon_corners",
    &pyigl::polygon_corners_kgon, 
    "Q"_a, 
R"(
\brief Convert a pure k-gon list of polygon mesh indices to list of
polygon corners and sizes
@param[in] Q  #Q by k list of polygon indices (ith row is a k-gon, unless Q(i,j) =
  -1 then it's a j-gon)
@param[out] I  #I vectorized list of polygon corner indices into rows of some matrix V
@param[out] C  #P+1 list of cumulative polygon sizes so that C(i+1)-C(i) = size of
    the ith polygon, and so I(C(i)) through I(C(i+1)-1) are the indices of
    the ith polygon

)");
}




