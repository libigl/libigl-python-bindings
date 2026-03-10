#include "default_types.h"
#include <igl/copyleft/cgal/peel_outer_hull_layers.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto peel_outer_hull_layers(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    // int32 required by libigl internals
    Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::VectorXi I;
    Eigen::Matrix<bool, Eigen::Dynamic, 1> flip;
    int n = igl::copyleft::cgal::peel_outer_hull_layers(V, Fi, I, flip);
    return std::make_tuple(Eigen::VectorXI(I.cast<Integer>()), Eigen::VectorXB(flip), n);
  }
}

void bind_peel_outer_hull_layers(nb::module_ &m)
{
  m.def("peel_outer_hull_layers", &pyigl::peel_outer_hull_layers, "V"_a, "F"_a,
    R"(Successively peel outer hull layers from a mesh, useful for boolean operations.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices into V
@return tuple (I, flip, num_peels):
  - I         #F list of which peel layer each facet belongs to
  - flip      #F list of bools, true if facet orientation was flipped during peeling
  - num_peels number of peel layers)");
}
