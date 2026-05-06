#include "default_types.h"
#include <igl/edges_to_path.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto edges_to_path(const nb::DRef<const Eigen::MatrixXI> &E)
  {
    // igl::edges_to_path internally uses Eigen::Map<DerivedE>(vE.data(), ...) where
    // vE is Eigen::VectorXi (int32). Must use Eigen::MatrixXi (int32, ColMajor).
    Eigen::MatrixXi e = E.cast<int>();
    Eigen::VectorXi I, J, K;
    igl::edges_to_path(e, I, J, K);
    // Cast int32 outputs back to int64 (Integer)
    return std::make_tuple(
      Eigen::VectorXI(I.cast<Integer>()),
      Eigen::VectorXI(J.cast<Integer>()),
      Eigen::VectorXI(K.cast<Integer>()));
  }
}

void bind_edges_to_path(nb::module_ &m)
{
  m.def("edges_to_path", &pyigl::edges_to_path, "E"_a,
    R"(Given undirected edges forming a single chain/loop, find the path visiting all nodes.

@param[in] E  #E by 2 list of undirected edges
@return I  #E+1 list of node indices tracing the chain (if loop: I[0]==I[-1])
@return J  #E list of indices into E tracing I
@return K  #E list of column indices in E (0 or 1) indicating edge direction)");
}
