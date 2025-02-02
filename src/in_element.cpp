#include "default_types.h"
#include <igl/in_element.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for in_element with simplicial mesh (F)
  auto in_element(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::MatrixXN> &Q,
    const igl::AABB<nb::DRef<const Eigen::MatrixXN>,3> &aabb)
  {
    Eigen::VectorXI I;
    igl::in_element(V,Ele,Q,aabb,I);
    return I;
  }

}

// Bind the wrapper to the Python module
void bind_in_element(nb::module_ &m)
{
  m.def(
    "in_element",
    &pyigl::in_element,
    "V"_a,
    "Ele"_a,
    "Q"_a,
    "aabb"_a,
R"(Determine whether each point in a list of points is in the elements of a
mesh.

@tparam  DIM  dimension of vertices in V (# of columns)
@param[in] V  #V by dim list of mesh vertex positions.
@param[in] Ele  #Ele by dim+1 list of mesh indices into #V.
@param[in] Q  #Q by dim list of query point positions
@param[in] aabb  axis-aligned bounding box tree object (see AABB.h)
@param[out] I  #Q list of indices into Ele of first containing element (-1 means no
    containing element)
)");
}
