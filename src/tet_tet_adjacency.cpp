#include "default_types.h"
#include <igl/tet_tet_adjacency.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto tet_tet_adjacency(const nb::DRef<const Eigen::MatrixXI> &T)
  {
    Eigen::MatrixXI TT, TTi;
    igl::tet_tet_adjacency(T, TT, TTi);
    return std::make_tuple(TT, TTi);
  }
}

void bind_tet_tet_adjacency(nb::module_ &m)
{
  m.def("tet_tet_adjacency", &pyigl::tet_tet_adjacency, "T"_a,
    R"(Construct tet-tet adjacency for a tet mesh.

Face order: [0,1,2], [0,1,3], [1,2,3], [2,0,3].

@param[in] T  #T by 4 list of tet indices
@return TT   #T by 4 matrix; TT(i,j) is the tet adjacent across face j of tet i
@return TTi  #T by 4 matrix; TTi(i,j) is the local face index in TT(i,j) shared with tet i)");
}
