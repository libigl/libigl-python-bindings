#include "default_types.h"
#include <igl/resolve_duplicated_faces.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto resolve_duplicated_faces(
    const nb::DRef<const Eigen::MatrixXI> &F1)
  {
    // resolve_duplicated_faces reuses the input's Derived type for internal
    // plain objects, so it needs a concrete matrix rather than an Eigen::Ref.
    const Eigen::MatrixXI F1c = F1;
    Eigen::MatrixXI F2;
    Eigen::VectorXI J;
    igl::resolve_duplicated_faces(F1c, F2, J);
    return std::make_tuple(F2, J);
  }
}

void bind_resolve_duplicated_faces(nb::module_ &m)
{
  m.def("resolve_duplicated_faces", &pyigl::resolve_duplicated_faces, "F1"_a,
    R"(Resolve duplicated faces according to the following rules per unique face:

1. If the number of positively oriented faces equals the number of negatively
   oriented faces, remove all duplicated faces at this triangle.
2. If the number of positively oriented faces equals the number of negatively
   oriented faces plus 1, keep one of the positively oriented faces.
3. If the number of positively oriented faces equals the number of negatively
   oriented faces minus 1, keep one of the negatively oriented faces.
4. If the number of positively oriented faces differs from the number of
   negatively oriented faces by more than 1, the mesh is not orientable at that
   triangle and all of its copies are dropped.

@param[in] F1  #F1 by 3 array of input faces
@return Tuple (F2, J) where
  F2  #F2 by 3 array of output faces without duplicated faces
  J   #F2 list of indices into F1)");
}
