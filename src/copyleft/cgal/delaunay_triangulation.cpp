#include "default_types.h"
#include <igl/copyleft/cgal/delaunay_triangulation.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto delaunay_triangulation(const nb::DRef<const Eigen::MatrixXN> &V)
  {
    Eigen::MatrixXi F;  // int32 required by libigl internals
    igl::copyleft::cgal::delaunay_triangulation(V, F);
    return Eigen::MatrixXI(F.cast<Integer>());
  }
}

void bind_delaunay_triangulation(nb::module_ &m)
{
  m.def("delaunay_triangulation", &pyigl::delaunay_triangulation, "V"_a,
    R"(Compute the Delaunay triangulation of a 2D point set using CGAL.

@param[in] V  #V by 2 list of 2D vertex positions
@return F  #F by 3 triangle indices into V)");
}
