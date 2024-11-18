#include "default_types.h"
#include <igl/isolines_intrinsic.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto isolines_intrinsic(
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &S,
    const nb::DRef<const Eigen::VectorXN> &vals)
  {
    Eigen::MatrixXN iB;
    Eigen::VectorXI iF;
    Eigen::MatrixXI iE;
    Eigen::VectorXI I;
    igl::isolines_intrinsic(F,S,vals,iB,iF,iE,I);
    return std::make_tuple(iB,iF,iE,I);
  }
  auto isolines_intrinsic_edges(
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXN> &S,
    const Numeric val,
    const nb::DRef<const Eigen::MatrixXI> &uE,
    const nb::DRef<const Eigen::VectorXI> &EMAP,
    const nb::DRef<const Eigen::VectorXI> &uEC,
    const nb::DRef<const Eigen::VectorXI> &uEE)
  {
    Eigen::MatrixXN iB;
    Eigen::VectorXI iF;
    Eigen::MatrixXI iE;
    igl::isolines_intrinsic(F,S,uE,EMAP,uEC,uEE,val,iB,iF,iE);
    return std::make_tuple(iB,iF,iE);
  }
}

// Bind the wrapper to the Python module
void bind_isolines_intrinsic(nb::module_ &m)
{
  m.def(
    "isolines_intrinsic",
    &pyigl::isolines_intrinsic,
    "F"_a,
    "S"_a,
    "vals"_a,
R"(Compute isolines of a scalar field on a triangle mesh intrinsically.

See isolines.h for details.

@param[in] F  #F by 3 list of mesh triangle indices into some V
@param[in] S  #S by 1 list of per-vertex scalar values
@param[in] vals  #vals by 1 list of values to compute isolines for
@param[out] iB  #iB by 3 list of barycentric coordinates so that 
  iV.row(i) = iB(i,0)*V.row(F(iFI(i,0)) +
              iB(i,1)*V.row(F(iFI(i,1)) +
              iB(i,2)*V.row(F(iFI(i,2))
@param[out] iF  #iB list of triangle indices for each row of iB (all
  points will either lie on an edge or vertex: an arbitrary incident face
  will be given).
@param[out] iE  #iE by 2 list of edge indices into iB
@param[out] I  #iE by 1 list of indices into vals indicating which value
  each segment belongs to

\see isolines, edge_crossings
)");
  m.def(
    "isolines_intrinsic",
    &pyigl::isolines_intrinsic_edges,
    "F"_a,
    "S"_a,
    "val"_a,
    "uE"_a,
    "EMAP"_a,
    "uEC"_a,
    "uEE"_a,
R"(Compute isolines of a scalar field on a triangle mesh intrinsically.

See isolines.h for details.

@param[in] F  #F by 3 list of mesh triangle indices into some V
@param[in] S  #S by 1 list of per-vertex scalar values
@param[in] val  scalar value to compute isoline at
@param[in] uE  #uE by 2 list of unique undirected edges
@param[in] EMAP #F*3 list of indices into uE, mapping each directed edge to unique
    undirected edge so that uE(EMAP(f+#F*c)) is the unique edge
    corresponding to E.row(f+#F*c)
@param[in] uEC  #uE+1 list of cumulative counts of directed edges sharing each
    unique edge so the uEC(i+1)-uEC(i) is the number of directed edges
    sharing the ith unique edge.
@param[in] uEE  #E list of indices into E, so that the consecutive segment of
    indices uEE.segment(uEC(i),uEC(i+1)-uEC(i)) lists all directed edges
    sharing the ith unique edge.
@param[out] iB  #iB by 3 list of barycentric coordinates so that 
  iV.row(i) = iB(i,0)*V.row(F(iFI(i,0)) +
              iB(i,1)*V.row(F(iFI(i,1)) +
              iB(i,2)*V.row(F(iFI(i,2))
@param[out] iF  #iB list of triangle indices for each row of iB (all
  points will either lie on an edge or vertex: an arbitrary incident face
  will be given).
@param[out] iE  #iE by 2 list of edge indices into iB

\see unique_edge_map
)");
}



