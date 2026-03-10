#include "default_types.h"
#include <igl/copyleft/cgal/extract_cells.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto extract_cells(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    // int32 required by libigl internals (static_assert checks index type)
    Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::MatrixXi cells;
    size_t n = igl::copyleft::cgal::extract_cells(V, Fi, cells);
    return std::make_tuple((Integer)n, Eigen::MatrixXI(cells.cast<Integer>()));
  }
}

void bind_extract_cells(nb::module_ &m)
{
  m.def("extract_cells", &pyigl::extract_cells, "V"_a, "F"_a,
    R"(Extract connected 3D cells partitioned by a triangle mesh.

@param[in] V  #V by 3 array of vertices
@param[in] F  #F by 3 array of triangle indices
@return tuple (num_cells, cells):
  - num_cells  number of cells (cell 0 is the infinite outer cell)
  - cells  #F by 2 array of cell indices; cells[i,0] is the cell on the
    positive side of face i, cells[i,1] is on the negative side)");
}
