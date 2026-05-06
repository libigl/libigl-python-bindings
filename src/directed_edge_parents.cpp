#include "default_types.h"
#include <igl/directed_edge_parents.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto directed_edge_parents(const nb::DRef<const Eigen::MatrixXI> &E)
  {
    Eigen::VectorXI P;
    igl::directed_edge_parents(E, P);
    return P;
  }
}

void bind_directed_edge_parents(nb::module_ &m)
{
  m.def("directed_edge_parents", &pyigl::directed_edge_parents, "E"_a,
    R"(Recover parent edges in a tree given directed edges.

@param[in] E  #E by 2 list of directed edges
@return P  #E list of parent indices into E (-1 means root))");
}
