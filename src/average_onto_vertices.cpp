#include "default_types.h"
#include <igl/average_onto_vertices.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto average_onto_vertices(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &S)
  {
    Eigen::VectorXN SV;
    igl::average_onto_vertices(V,F,S,SV);
    return SV;
  }
}

// Bind the wrapper to the Python module
void bind_average_onto_vertices(nb::module_ &m)
{
  m.def(
    "average_onto_vertices", 
    &pyigl::average_onto_vertices, 
    "V"_a,
    "F"_a,
    "S"_a,
R"(Move a scalar field defined on faces to vertices by averaging
  
@param[in] S #V by dim triangle mesh connectivity
@param[in] F #F by 3 triangle mesh connectivity
@param[in] S #F by 1 scalar field defined on faces
@param[out] SV #V by 1 scalar field defined on vertices
)"
    );
}

