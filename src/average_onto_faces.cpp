#include "default_types.h"
#include <igl/average_onto_faces.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto average_onto_faces(
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &S)
  {
    Eigen::VectorXN SF;
    igl::average_onto_faces(F,S,SF);
    return SF;
  }
}

// Bind the wrapper to the Python module
void bind_average_onto_faces(nb::module_ &m)
{
  m.def(
    "average_onto_faces", 
    &pyigl::average_onto_faces, 
    "F"_a,
    "S"_a,
R"(Move a scalar field defined on faces to faces by averaging
  
@param[in] F #F by 3 triangle mesh connectivity
@param[in] S #F by 1 scalar field defined on faces
@param[out] SF #F by 1 scalar field defined on faces
)"
    );
}


