#include "default_types.h"
#include <igl/sample_edges.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto sample_edges(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &E,
    const int k)
  {
    // igl::sample_edges takes MatrixXd and MatrixXi (int32, ColMajor)
    Eigen::MatrixXd v = V;
    Eigen::MatrixXi e = E.cast<int>();
    Eigen::MatrixXd S;
    igl::sample_edges(v, e, k, S);
    return Eigen::MatrixXN(S);
  }
}

void bind_sample_edges(nb::module_ &m)
{
  m.def("sample_edges", &pyigl::sample_edges, "V"_a, "E"_a, "k"_a,
    R"(Compute k extra sample points along each edge.

@param[in] V  #V by dim list of vertex positions
@param[in] E  #E by 2 list of edge indices into V
@param[in] k  number of extra samples per edge (not including endpoints)
@return S  sampled positions; begins with V so E still indexes into S)");
}
