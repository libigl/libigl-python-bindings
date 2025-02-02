#include "default_types.h"
#include <igl/face_areas.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto face_areas(
    const nb::DRef<const Eigen::MatrixXN>& V,
    const nb::DRef<const Eigen::MatrixXI>& T)
  {
    Eigen::MatrixXN A;
    igl::face_areas(V, T, A);
    return A;
  }
}

void bind_face_areas(nb::module_ &m)
{
  m.def("face_areas", &pyigl::face_areas,
    "V"_a,
    "T"_a,
    R"(Constructs a list of face areas of faces opposite each index in a tet list
@param[in] V  #V by 3 list of mesh vertex positions
@param[in] T  #T by 3 list of tet mesh indices into V
@param[out] A   #T by 4 list of face areas corresponding to faces opposite vertices
    0,1,2,3)");
}
