#include "default_types.h"
#include <igl/vertex_triangle_adjacency.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto vertex_triangle_adjacency(
    const nb::DRef<const Eigen::MatrixXI> &F,
    Integer n)
  {
    if(n==0 && F.size()>0)
    {
      n = F.maxCoeff()+1;
    }
    Eigen::VectorXI VF,NI;
    igl::vertex_triangle_adjacency(F,n,VF,NI);
    return std::make_tuple(VF,NI);
  }
  auto vertex_triangle_adjacency_lists(
    const nb::DRef<const Eigen::MatrixXI> &F,
    Integer n)
  {
    if(n==0 && F.size()>0)
    {
      n = F.maxCoeff()+1;
    }
    std::vector<std::vector<Integer>> VF,VFi;
    igl::vertex_triangle_adjacency(n,F,VF,VFi);
    return std::make_tuple(VF,VFi);
  }
}

// Bind the wrapper to the Python module
void bind_vertex_triangle_adjacency(nb::module_ &m)
{
  m.def(
    "vertex_triangle_adjacency",
    &pyigl::vertex_triangle_adjacency, 
    "F"_a,
    "n"_a=0,
R"(vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

 @param[in] F  #F by dim list of mesh faces (must be triangles)
 @param[in] n  number of vertices #V (e.g. `F.maxCoeff()+1` or `V.rows()`)
 @param[out] VF  #V list of lists of incident faces (adjacency list)
 @param[out] VI  #V list of lists of index of incidence within incident faces listed
     in VF
    );)"
    );
  m.def(
    "vertex_triangle_adjacency_lists",
    &pyigl::vertex_triangle_adjacency_lists, 
    "F"_a,
    "n"_a=0,
R"(vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

 @param[in] F  #F by dim list of mesh faces (must be triangles)
 @param[in] n  number of vertices #V (e.g. `F.maxCoeff()+1` or `V.rows()`)
 if using lists
 @param[out] VF  #V list of lists of incident faces (adjacency list)
 @param[out] VI  #V list of lists of index of incidence within incident faces listed
     in VF)"
    );
}




