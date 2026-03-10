#include "default_types.h"
#include <igl/is_delaunay.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto is_delaunay(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::Array<bool, Eigen::Dynamic, Eigen::Dynamic> D;
    igl::is_delaunay(V, F, D);
    return D;
  }
}

void bind_is_delaunay(nb::module_ &m)
{
  m.def("is_delaunay", &pyigl::is_delaunay, "V"_a, "F"_a,
    R"(Determine if each edge in a mesh is locally Delaunay.

@param[in] V  #V by dim list of vertex positions
@param[in] F  #F by 3 list of triangle indices
@return D  #F by 3 bool array; D(f,e) is true iff edge e of face f is locally
  Delaunay. Boundary edges are Delaunay by definition.)");
}
