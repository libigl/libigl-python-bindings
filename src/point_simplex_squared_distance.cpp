#include "default_types.h"
#include <igl/point_simplex_squared_distance.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto point_simplex_squared_distance(
    const nb::DRef<const Eigen::RowVectorXN> &p,
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const Integer i)
  {
    // Use concrete Eigen types (template deduction is finicky with DRef maps here).
    // DIM (the ambient dimension) is a non-deduced template parameter, so we must
    // supply it explicitly; dispatch on the number of columns of V.
    const Eigen::RowVectorXN pc = p;
    const Eigen::MatrixXN Vc = V;
    const Eigen::MatrixXI Elec = Ele;
    Numeric sqr_d;
    Eigen::RowVectorXN c;
    Eigen::RowVectorXN b;
    switch (Vc.cols())
    {
      case 2:
        igl::point_simplex_squared_distance<2>(pc, Vc, Elec, i, sqr_d, c, b);
        break;
      case 3:
        igl::point_simplex_squared_distance<3>(pc, Vc, Elec, i, sqr_d, c, b);
        break;
      default:
        throw std::runtime_error(
          "point_simplex_squared_distance: only 2D and 3D points are supported");
    }
    return std::make_tuple(sqr_d, c, b);
  }
}

void bind_point_simplex_squared_distance(nb::module_ &m)
{
  m.def(
    "point_simplex_squared_distance",
    &pyigl::point_simplex_squared_distance,
    "p"_a,
    "V"_a,
    "Ele"_a,
    "i"_a,
R"(Determine the squared distance from a point p to the i-th linear simplex
(point/segment/triangle) of a mesh, along with the closest point and its
barycentric coordinates.

@param[in] p  dim-long query point
@param[in] V  #V by dim list of simplex-corner vertex positions
@param[in] Ele  #Ele by (1|2|3) list of simplex indices into rows of V
@param[in] i  index of the simplex (row of Ele) to measure against
@param[out] sqr_d  squared distance from p to the i-th simplex
@param[out] c  dim-long closest point on the i-th simplex
@param[out] b  barycentric coordinates of the closest point c)");
}
