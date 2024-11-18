#include "default_types.h"
#include <igl/collapse_edge.h>
#include <igl/matlab_format.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto collapse_edge(
    const Integer e,
    const nb::DRef<const Eigen::RowVectorXN> &p,
    Eigen::Ref<Eigen::MatrixXN> V,
    Eigen::Ref<Eigen::MatrixXI> F,
    Eigen::Ref<Eigen::MatrixXI> E,
    Eigen::Ref<Eigen::VectorXI> EMAP,
    Eigen::Ref<Eigen::MatrixXI> EF,
    Eigen::Ref<Eigen::MatrixXI> EI)
  {
    int e1_,e2_,f1_,f2_;
    if(!igl::collapse_edge(e,p,V,F,E,EMAP,EF,EI,e1_,e2_,f1_,f2_))
    {
      throw std::runtime_error("collapse_edge failed");
    }

    Integer e1 = e1_,e2 = e2_,f1 = f1_,f2 = f2_;
    return std::make_tuple(e1,e2,f1,f2);
  }

}

// Bind the wrapper to the Python module
void bind_collapse_edge(nb::module_ &m)
{
  m.def(
    "collapse_edge",
    &pyigl::collapse_edge, 
    "e"_a,
    "p"_a,
    nb::arg("V").noconvert(),
    nb::arg("F").noconvert(),
    nb::arg("E").noconvert(),
    nb::arg("EMAP").noconvert(),
    nb::arg("EF").noconvert(),
    nb::arg("EI").noconvert(),
R"(Attempt to collapse a given edge of a mesh. Assumes (V,F) is a closed
manifold mesh (except for previously collapsed faces which should be set
to: [IGL_COLLAPSE_EDGE_NULL IGL_COLLAPSE_EDGE_NULL
IGL_COLLAPSE_EDGE_NULL]. Collapses exactly two faces and exactly 3 edges
from E (e and one side of each face gets collapsed to the other). This is
implemented in a way that it can be repeatedly called until satisfaction
and then the garbage in F can be collected by removing NULL faces.

@param[in] e  index into E of edge to try to collapse. E(e,:) = [s d] or [d s] so
    that s<d, then d is collapsed to s.
@param[in] p  dim list of vertex position where to place merged vertex
[mesh inputs]
@param[in,out] V  #V by dim list of vertex positions, lesser index of E(e,:) will be set
    to midpoint of edge.
@param[in,out] F  #F by 3 list of face indices into V.
@param[in,out] E  #E by 2 list of edge indices into V.
@param[in,out] EMAP #F*3 list of indices into E, mapping each directed edge to unique
    unique edge in E
@param[in,out] EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
    F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
    e=(j->i)
@param[in,out] EI  #E by 2 list of edge flap corners (see above).
[mesh inputs]
@param[out] e1  index into E of edge collpased on left
@param[out] e2  index into E of edge collpased on right
@param[out] f1  index into F of face collpased on left
@param[out] f2  index into F of face collpased on right
@return true if edge was collapsed

Because there are side-effects on V,F,E,EMAP,EF,EI, this function will not
accept all numpy variations and will refuse to copy inputs that don't match
expected ordering and dtype.
)");
}




