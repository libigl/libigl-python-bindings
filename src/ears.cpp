#include "default_types.h"
#include <igl/ears.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto ears(
    const nb::DRef<const Eigen::MatrixXI> & F)
  {
    Eigen::VectorXI ear,ear_opp;
    igl::ears(F,ear,ear_opp);
    return std::make_tuple(ear,ear_opp);
  }
}

void bind_ears(nb::module_ &m)
{
  m.def("ears", &pyigl::ears,
    "F"_a,
    R"(Find all ears (faces with two boundary edges) in a given mesh

@param[in] F  #F by 3 list of triangle mesh indices
@param[out] ears  #ears list of indices into F of ears
@param[out] ear_opp  #ears list of indices indicating which edge is non-boundary
    (connecting to flops))");
}
