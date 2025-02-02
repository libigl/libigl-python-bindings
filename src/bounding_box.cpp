#include "default_types.h"
#include <igl/bounding_box.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto bounding_box(
    const nb::DRef<const Eigen::MatrixXN>& V,
    const Numeric pad)
  {
    Eigen::MatrixXN BV;
    Eigen::MatrixXI BF;
    igl::bounding_box(V, pad, BV, BF);
    return std::make_tuple(BV, BF);
  }
}

void bind_bounding_box(nb::module_ &m)
{
  m.def("bounding_box", &pyigl::bounding_box,
    "V"_a,
    "pad"_a=0,
    R"(Build a triangle mesh of the bounding box of a given list of vertices

@param[in]  V  #V by dim list of rest domain positions
@param[in]  pad  padding offset
@param[out] BV  2^dim by dim list of bounding box corners positions
@param[out] BF  #BF by dim list of simplex facets )");
}
