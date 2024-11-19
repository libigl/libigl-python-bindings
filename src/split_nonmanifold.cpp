#include "default_types.h"
#include <igl/split_nonmanifold.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto split_nonmanifold(
    const nb::DRef<const Eigen::MatrixXI> & F)
  {
    Eigen::MatrixXI SF;
    Eigen::VectorXI SVI;
    igl::split_nonmanifold(F, SF, SVI);
    return std::make_tuple(SF, SVI);
  }
  auto split_nonmanifold_VF(
    const nb::DRef<const Eigen::MatrixXN> & V,
    const nb::DRef<const Eigen::MatrixXI> & F)
  {
    Eigen::MatrixXI SF;
    Eigen::MatrixXN SV;
    Eigen::VectorXI SVI;
    igl::split_nonmanifold(V, F, SV, SF, SVI);
    return std::make_tuple(SV, SF, SVI);
  }
}

void bind_split_nonmanifold(nb::module_ &m)
{
  m.def("split_nonmanifold", &pyigl::split_nonmanifold,
    "F"_a,
    R"(Split a non-manifold (or non-orientable) mesh into a orientable manifold
mesh possibly with more connected components and geometrically duplicate
vertices.
@param[in] F  #F by 3 list of mesh triangle indices into rows of some V
@param[out] SF  #F by 3 list of mesh triangle indices into rows of a new vertex list
              SV = V(SVI,:)
@param[out] SVI  #SV list of indices into V identifying vertex positions)");
  m.def("split_nonmanifold", &pyigl::split_nonmanifold_VF,
    "V"_a,
    "F"_a,
    R"(Split a non-manifold (or non-orientable) mesh into a orientable manifold
mesh possibly with more connected components and geometrically duplicate
vertices.
@param[in] V  #V by dim explicit list of vertex positions
@param[in] F  #F by 3 list of mesh triangle indices into rows of some V
@param[out] SV  #SV by dim explicit list of vertex positions
@param[out] SF  #F by 3 list of mesh triangle indices into rows of a new vertex list
              SV = V(SVI,:)
@param[out] SVI  #SV list of indices into V identifying vertex positions)");
}
