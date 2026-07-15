#include "default_types.h"
#include <igl/resolve_duplicated_faces.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto resolve_duplicated_faces(const nb::DRef<const Eigen::MatrixXI> &F1)
  {
    // Copy to PlainObjectBase so libigl can default-construct DerivedF1 internally
    Eigen::MatrixXI F1_copy = F1;
    Eigen::MatrixXI F2;
    Eigen::VectorXI J;
    igl::resolve_duplicated_faces(F1_copy, F2, J);
    return std::make_tuple(F2, J);
  }
}

void bind_resolve_duplicated_faces(nb::module_ &m)
{
  m.def(
    "resolve_duplicated_faces",
    &pyigl::resolve_duplicated_faces,
    "F1"_a,
    R"(Resolve duplicated faces according to orientation cancellation rules.

Pairs of oppositely oriented duplicate faces cancel each other out; a net
excess of one positively (or negatively) oriented copy is kept; a net
difference greater than one means the mesh is not orientable and an
exception is thrown.

@param[in] F1  #F1 by 3 array of input faces
@return Tuple containing:
        - F2: #F2 by 3 array of output faces without duplicated faces
        - J:  #F2 list of indices into F1)");
}
