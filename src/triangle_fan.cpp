#include "default_types.h"
#include <igl/triangle_fan.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto triangle_fan(
    const nb::DRef<const Eigen::MatrixXI> & E)
  {
    Eigen::MatrixXI cap;
    igl::triangle_fan(E, cap);
    return cap;
  }
}

void bind_triangle_fan(nb::module_ &m)
{
  m.def("triangle_fan", &pyigl::triangle_fan,
    "E"_a,
    R"(Given a list of faces tessellate all of the "exterior" edges forming another
list of 
@param[in] E  #E by simplex_size-1  list of exterior edges (see exterior_edges.h)
@param[out] cap  #cap by simplex_size  list of "faces" tessellating the boundary edges)");
}
