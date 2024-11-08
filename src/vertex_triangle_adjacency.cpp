#include "default_types.h"
#include <igl/vertex_triangle_adjacency.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  nb::object vertex_triangle_adjacency(
    const nb::DRef<const Eigen::MatrixXI> &F,
    Integer n,
    const nb::DRef<const Eigen::MatrixXN> &V,
    bool return_VFi,
    bool use_lists)
  {
    n = n ? n : (V.rows() ? V.rows() : F.maxCoeff()+1);
    if(use_lists)
    {
      std::vector<std::vector<Integer>> VF,VFi;
      igl::vertex_triangle_adjacency(n,F,VF,VFi);
      if(return_VFi)
      {
        return nb::make_tuple(VF,VFi);
      }else
      {
        return nb::cast(std::move(VF));
      }
    }else
    {
      if(return_VFi)
      {
        throw std::runtime_error("vertex_triangle_adjacency: NI and VFI are mutually exclusive");
      }
      Eigen::VectorXI VF,NI;
      igl::vertex_triangle_adjacency(F,n,VF,NI);
      return nb::make_tuple(VF,NI);
    }
  }
}

// Bind the wrapper to the Python module
void bind_vertex_triangle_adjacency(nb::module_ &m)
{
  m.def(
    "vertex_triangle_adjacency",
    &pyigl::vertex_triangle_adjacency, 
    "F"_a=Eigen::MatrixXI(), 
    "n"_a=Integer(0),
    "V"_a=Eigen::MatrixXN(),
    "return_VFi"_a=false,
    "use_lists"_a=false,
R"(vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

 @param[in] n  number of vertices #V (e.g. `F.maxCoeff()+1` or `V.rows()`)
 @param[in] F  #F by dim list of mesh faces (must be triangles)
 @param[out] VF  #V list of lists of incident faces (adjacency list)
 @param[out] VI  #V list of lists of index of incidence within incident faces listed
     in VF

 \see edges, cotmatrix, diag, vv

 \bug this should not take V as an input parameter.
 \bug if a facet is combinatorially degenerate then faces will appear
 multiple times in VF and correspondingly in VFI (j appears twice in
 F.row(i) then i will appear twice in VF[j])

 @param[in] F  #F by 3 list of triangle indices into some vertex list V
 @param[in] n  number of vertices, #V (e.g., F.maxCoeff()+1)
 @param[out] VF  3*#F list  List of faces indice on each vertex, so that VF(NI(i)+j) =
     f, means that face f is the jth face (in no particular order) incident
     on vertex i.
 @param[out] NI  #V+1 list  cumulative sum of vertex-triangle degrees with a
     preceeding zero. "How many faces" have been seen before visiting this
     vertex and its incident faces.)"
    );
}




