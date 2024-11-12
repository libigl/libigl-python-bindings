#include "default_types.h"
#include <igl/project_to_line_segment.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for project_to_line_segment function
  auto project_to_line_segment(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::RowVectorXN> &S,
    const nb::DRef<const Eigen::RowVectorXN> &D)
  {
    Eigen::VectorXN t;
    Eigen::VectorXN sqrD;
    igl::project_to_line_segment(P, S, D, t, sqrD);
    return std::make_tuple(t, sqrD);
  }
}

// Bind the wrapper to the Python module
void bind_project_to_line_segment(nb::module_ &m)
{
  m.def(
    "project_to_line_segment",
    &pyigl::project_to_line_segment,
    "P"_a,
    "S"_a,
    "D"_a,
    R"(Project points onto a line segment defined by points S and D.
    
    @param[in] P  #P by dim list of points to be projected
    @param[in] S  1 by dim starting position of line segment
    @param[in] D  1 by dim ending position of line segment
    @return Tuple containing:
            - t: #P by 1 list of parameters along the line segment for each point
            - sqrD: #P by 1 list of squared distances from each point to its projection)"
  );
}
