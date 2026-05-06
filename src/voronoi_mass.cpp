#include "default_types.h"
#include <igl/voronoi_mass.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto voronoi_mass(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &T)
  {
    Eigen::VectorXN M;
    igl::voronoi_mass(V, T, M);
    return M;
  }
}

void bind_voronoi_mass(nb::module_ &m)
{
  m.def("voronoi_mass", &pyigl::voronoi_mass, "V"_a, "T"_a,
    R"(Compute hybrid Voronoi mass matrix entries for a tetrahedral mesh.

@param[in] V  #V by 3 list of vertex positions
@param[in] T  #T by 4 list of tet indices into V
@return M  #V list of mass matrix diagonal entries (positive for non-degenerate tets))");
}
