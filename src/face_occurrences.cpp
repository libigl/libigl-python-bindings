#include "default_types.h"
#include <igl/face_occurrences.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto face_occurrences(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXI C;
    igl::face_occurrences(F, C);
    return C;
  }
}

void bind_face_occurrences(nb::module_ &m)
{
  m.def("face_occurrences", &pyigl::face_occurrences, "F"_a,
    R"(Count the occurrences of each face (row) in a list of face indices.

@param[in] F  #F by simplex_size list of faces
@return C  #F list of occurrence counts)");
}
