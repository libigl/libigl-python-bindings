#include "default_types.h"
#include <igl/is_intrinsic_delaunay.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto is_intrinsic_delaunay(
      const nb::DRef<const Eigen::MatrixXN> &l,
      const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> D;
    igl::is_intrinsic_delaunay(l, F, D);
    return D;
  }
}

void bind_is_intrinsic_delaunay(nb::module_ &m)
{
  m.def("is_intrinsic_delaunay", &pyigl::is_intrinsic_delaunay,
        "l"_a,
        "F"_a,
        R"(Determine if each edge in the mesh (V,F) is Delaunay.
@param[in] l  #l by dim list of edge lengths
@param[in] F  #F by 3 list of triangles indices
@param[out] D  D #F by 3 list of bools revealing whether edges corresponding
    23 31 12 are locally Delaunay. Boundary edges are by definition Delaunay.
    Non-Manifold edges are by definition not Delaunay.
)");
}
