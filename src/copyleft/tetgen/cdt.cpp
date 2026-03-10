#include "default_types.h"
#include <igl/copyleft/tetgen/cdt.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto cdt(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const igl::copyleft::tetgen::CDTParam &param)
  {
    // int32 required by libigl tetgen internals
    Eigen::MatrixXi Fi = F.cast<int>();
    Eigen::MatrixXN TV;
    Eigen::MatrixXi TT, TF;
    // Note: libigl cdt() returns tetrahedralize()'s int (0=success) cast to
    // bool, so false means success. Check output TT instead.
    igl::copyleft::tetgen::cdt(V, Fi, param, TV, TT, TF);
    if(TT.rows() == 0)
      throw std::runtime_error("cdt: tetrahedralization failed");
    return std::make_tuple(TV, Eigen::MatrixXI(TT.cast<Integer>()),
      Eigen::MatrixXI(TF.cast<Integer>()));
  }
}

void bind_cdt(nb::module_ &m)
{
  nb::class_<igl::copyleft::tetgen::CDTParam>(m, "CDTParam")
    .def(nb::init<>())
    .def_rw("use_bounding_box",    &igl::copyleft::tetgen::CDTParam::use_bounding_box)
    .def_rw("bounding_box_scale",  &igl::copyleft::tetgen::CDTParam::bounding_box_scale)
    .def_rw("flags",               &igl::copyleft::tetgen::CDTParam::flags);

  m.def("cdt", &pyigl::cdt,
    "V"_a, "F"_a, "param"_a = igl::copyleft::tetgen::CDTParam{},
    R"(Create a constrained Delaunay tetrahedralization of the convex hull of a mesh.

The input mesh must be non-self-intersecting.

@param[in] V  #V by 3 list of input mesh vertices
@param[in] F  #F by 3 list of input mesh facets
@param[in] param  CDTParam struct with fields:
    use_bounding_box    force meshing of the bounding box (default: false)
    bounding_box_scale  scale factor for bounding box (default: 1.01)
    flags               tetgen flags, do not include "c" (default: "Y")
@return tuple (TV, TT, TF):
  - TV  #TV by 3 output vertex positions (input vertices come first)
  - TT  #TT by 4 tetrahedra indices into TV
  - TF  #TF by 3 surface triangle indices (facets from F, possibly subdivided)
@raises RuntimeError on failure)");
}
