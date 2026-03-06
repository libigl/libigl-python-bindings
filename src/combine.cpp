#include "default_types.h"
#include <igl/combine.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto combine(
    const std::vector<Eigen::MatrixXN> &VV,
    const std::vector<Eigen::MatrixXI> &FF)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI F;
    igl::combine(VV, FF, V, F);
    return std::make_tuple(V, F);
  }
}

void bind_combine(nb::module_ &m)
{
  m.def("combine", &pyigl::combine, "VV"_a, "FF"_a,
    R"(Concatenate multiple meshes into a single mesh.

@param[in] VV  list of vertex position matrices, each #Vi by dim
@param[in] FF  list of face index matrices, each #Fi by simplex_size
@return V  concatenated vertex positions
@return F  concatenated face indices (reindexed into V))");
}
