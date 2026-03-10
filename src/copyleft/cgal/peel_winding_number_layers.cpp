#include "default_types.h"
#include <igl/copyleft/cgal/peel_winding_number_layers.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto peel_winding_number_layers(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    // int32 required by libigl internals
    Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::VectorXi W;
    size_t n = igl::copyleft::cgal::peel_winding_number_layers(V, Fi, W);
    return std::make_tuple(Eigen::VectorXI(W.cast<Integer>()), (Integer)n);
  }
}

void bind_peel_winding_number_layers(nb::module_ &m)
{
  m.def("peel_winding_number_layers", &pyigl::peel_winding_number_layers, "V"_a, "F"_a,
    R"(Peel winding number layers from a mesh.

@param[in] V  #V by 3 list of vertex positions
@param[in] F  #F by 3 list of triangle indices into V
@return tuple (W, num_layers):
  - W          #V list of integer winding numbers per vertex
  - num_layers number of winding number layers)");
}
