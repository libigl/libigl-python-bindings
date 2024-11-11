#include "default_types.h"
#include <igl/on_boundary.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto on_boundary(
    const nb::DRef<const Eigen::MatrixXI> &T)
  {
    Eigen::VectorX<bool> I;              // Output: boundary indicator for each element
    Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> C;  // Output: boundary facets per element

    igl::on_boundary(T, I, C);

    return std::make_tuple(I, C);
  }
}

// Bind the wrapper to the Python module
void bind_on_boundary(nb::module_ &m)
{
  m.def(
    "on_boundary",
    &pyigl::on_boundary,
    "T"_a,
R"(Determine boundary facets of mesh elements stored in T.

@param[in] T  m by 3|4 list of triangle or tetrahedron indices, where m is the number of elements
@return Tuple containing:
  - I: m-length vector of bools indicating if each element is on the boundary
  - C: m by 3|4 matrix of bools indicating if each opposite facet is on the boundary)");
}
