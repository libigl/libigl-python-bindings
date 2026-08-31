#include "default_types.h"
#include <igl/path_to_edges.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto path_to_edges(
    const nb::DRef<const Eigen::VectorXI> &I,
    const bool make_loop)
  {
    Eigen::MatrixXI E;
    igl::path_to_edges(I, E, make_loop);
    return E;
  }
}

void bind_path_to_edges(nb::module_ &m)
{
  m.def(
    "path_to_edges",
    &pyigl::path_to_edges,
    "I"_a,
    "make_loop"_a = false,
R"(Given an ordered list of vertex indices describing a path, return the list
of undirected edges connecting consecutive entries.

@param[in] I  #I list of vertex indices along the path
@param[in] make_loop  whether to also connect the last vertex back to the first
@param[out] E  #E by 2 list of edges (E = #I-1, or #I if make_loop))");
}
