#include "default_types.h"
#include <igl/lexicographic_triangulation.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto lexicographic_triangulation(
    const Eigen::MatrixXN &P)
  {
    auto orient2D = [](const Numeric* pa, const Numeric* pb, const Numeric* pc) -> int
    {
      const Numeric cross =
        (pb[0] - pa[0]) * (pc[1] - pa[1]) -
        (pb[1] - pa[1]) * (pc[0] - pa[0]);
      return (cross > 0) ? 1 : (cross < 0) ? -1 : 0;
    };
    Eigen::MatrixXi F;
    try
    {
      igl::lexicographic_triangulation(P, orient2D, F);
    }
    catch(const char* e)
    {
      throw std::runtime_error(e);
    }
    return F;
  }
}

void bind_lexicographic_triangulation(nb::module_ &m)
{
  m.def(
    "lexicographic_triangulation",
    &pyigl::lexicographic_triangulation,
    "P"_a,
R"(Compute a lexicographic triangulation of a 2D point set.

Uses a floating-point cross-product orientation predicate; may be inaccurate
for nearly-collinear inputs.

@param[in] P  #P by 2 list of 2D vertex positions
@param[out] F  #F by 3 list of face indices into P)");
}
