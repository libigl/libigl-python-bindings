#include "default_types.h"
#include <igl/quad_edges.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto quad_edges(const nb::DRef<const Eigen::MatrixXI> &Q)
  {
    // igl::quad_edges is instantiated only for 32-bit int matrices (it builds an
    // Eigen::MatrixXi internally), so cast to int and back.
    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> Qi = Q.cast<int>();
    Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> Ei;
    igl::quad_edges(Qi, Ei);
    return Eigen::MatrixXI(Ei.cast<Integer>());
  }
}

void bind_quad_edges(nb::module_ &m)
{
  m.def(
    "quad_edges",
    &pyigl::quad_edges,
    "Q"_a,
R"(Compute the list of unique undirected edges of a quad mesh.

@param[in] Q  #Q by 4 list of quad face indices
@param[out] E  #E by 2 list of unique edges)");
}
