#include "default_types.h"
#include <igl/remove_duplicate_vertices.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Binding for remove_duplicate_vertices without face remapping
  auto remove_duplicate_vertices(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const double epsilon)
  {
    Eigen::MatrixXN SV;
    Eigen::VectorXI SVI, SVJ;
    igl::remove_duplicate_vertices(V, epsilon, SV, SVI, SVJ);
    return std::make_tuple(SV, SVI, SVJ);
  }

  // Binding for remove_duplicate_vertices with face remapping
  auto remove_duplicate_vertices_F(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const double epsilon)
  {
    Eigen::MatrixXN SV;
    Eigen::VectorXI SVI, SVJ;
    Eigen::MatrixXI SF;
    igl::remove_duplicate_vertices(V, F, epsilon, SV, SVI, SVJ, SF);
    return std::make_tuple(SV, SVI, SVJ, SF);
  }
}

// Bind the wrapper to the Python module
void bind_remove_duplicate_vertices(nb::module_ &m)
{
  m.def(
    "remove_duplicate_vertices",
    &pyigl::remove_duplicate_vertices,
    "V"_a,
    "epsilon"_a,
    R"(Remove duplicate vertices up to a uniqueness tolerance (epsilon).

    @param[in] V  #V by dim list of vertex positions
    @param[in] epsilon  Uniqueness tolerance used coordinate-wise
    @return Tuple containing:
            - SV: #SV by dim new list of unique vertex positions
            - SVI: #SV list of indices so SV = V(SVI,:)
            - SVJ: #V list of indices so V = SV(SVJ,:))");

  m.def(
    "remove_duplicate_vertices",
    &pyigl::remove_duplicate_vertices_F,
    "V"_a,
    "F"_a,
    "epsilon"_a,
    R"(Remove duplicate vertices and remap faces to new indices.

    @param[in] V  #V by dim list of vertex positions
    @param[in] F  #F by dim list of face indices
    @param[in] return_SVJ  If true, return the SVJ mapping indices
    @return Tuple containing:
            - SV: #SV by dim new list of unique vertex positions
            - SVI: #SV list of indices so SV = V(SVI,:)
            - SVJ: #V list of indices so V = SV(SVJ,:)
            - SF: #F by dim list of remapped face indices into SV)");
}
