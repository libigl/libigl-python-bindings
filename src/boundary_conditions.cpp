#include "default_types.h"
#include <igl/boundary_conditions.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto boundary_conditions(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &Ele,
    const nb::DRef<const Eigen::MatrixXN> &C,
    const nb::DRef<const Eigen::VectorXI> &P,
    const nb::DRef<const Eigen::MatrixXI> &BE,
    const nb::DRef<const Eigen::MatrixXI> &CE,
    const nb::DRef<const Eigen::MatrixXI> &CF)
  {

    Eigen::VectorXI b;
    Eigen::MatrixXN bc;
    if(!igl::boundary_conditions(V, Ele, C, P, BE, CE, CF, b, bc))
    {
      throw std::runtime_error("boundary_conditions: failed to compute");
    }
    return std::make_tuple(b, bc);
  }
}

void bind_boundary_conditions(nb::module_ &m)
{
  m.def(
    "boundary_conditions", 
    &pyigl::boundary_conditions,
    "V"_a,
    "Ele"_a,
    "C"_a,
    "P"_a=Eigen::VectorXI(),
    "BE"_a=Eigen::MatrixXI(),
    "CE"_a=Eigen::MatrixXI(),
    "CF"_a=Eigen::MatrixXI(),
R"(Compute boundary conditions for automatic weights computation. This
function expects that the given mesh (V,Ele) has sufficient samples
(vertices) exactly at point handle locations and exactly along bone and
cage edges/faces.
@param[in] V  #V by dim list of domain vertices
@param[in] Ele  #Ele by simplex-size list of simplex indices
@param[in] C  #C by dim list of handle positions
@param[in] P  #P by 1 list of point handle indices into C
@param[in] BE  #BE by 2 list of bone edge indices into C
@param[in] CE  #CE by 2 list of cage edge indices into *P*
@param[in] CF  #CF by 3 list of (triangular) cage face indices into *P*
@param[out] b  #b list of boundary indices (indices into V of vertices which have
    known, fixed values)
@param[out] bc #b by #weights list of known/fixed values for boundary vertices
    (notice the #b != #weights in general because #b will include all the
    intermediary samples along each bone, etc.. The ordering of the
    weights corresponds to [P;BE]
throws error if boundary conditions are suspicious:
  P and BE are empty
  bc is empty
  some column of bc doesn't have a 0 (assuming bc has >1 columns)
  some column of bc doesn't have a 1 (assuming bc has >1 columns))"
  );
}
