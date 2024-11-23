#include "default_types.h"
#include <igl/cut_mesh_from_singularities.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto cut_mesh_from_singularities(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXI> &MMatch)
  {
    Eigen::MatrixXB seams;
    igl::cut_mesh_from_singularities(V, F, MMatch, seams);
    return seams;
  }
}

void bind_cut_mesh_from_singularities(nb::module_ &m)
{
  m.def("cut_mesh_from_singularities", &pyigl::cut_mesh_from_singularities,
    "V"_a,
    "F"_a,
    "MMatch"_a,
    R"(Given a mesh (V,F) and the integer mismatch of a cross field per edge
(mismatch), finds the cut_graph connecting the singularities (seams) and the
degree of the singularities singularity_index
@param[in] V  #V by 3 list of mesh vertex positions
@param[in] F  #F by 3 list of faces
@param[in] mismatch  #F by 3 list of per corner integer mismatch
@param[out] seams  #F by 3 list of per corner booleans that denotes if an edge is a
    seam or not)");
}
