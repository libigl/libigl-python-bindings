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
    bool use_lists,
    bool return_VFi)
  {
    if(n==0 && F.size()>0)
    {
      n = F.maxCoeff()+1;
    }
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
        throw std::runtime_error("vertex_triangle_adjacency: use_lists must be true to return VFi");
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
    "F"_a,
    "n"_a=0,
    "use_lists"_a=false,
    "return_VFi"_a=false,
R"(vertex_face_adjacency constructs the vertex-face topology of a given mesh (V,F)

 @param[in] F  #F by dim list of mesh faces (must be triangles)
 @param[in] n  number of vertices #V (e.g. `F.maxCoeff()+1` or `V.rows()`)
 @param[in] use_lists  whether to return the result as a list of lists or as a pair of Eigen matrices
 @param[in] return_VFi  whether to return the list of lists of index of incidence within incident faces listed in VF
 if using lists
 @param[out] VF  #V list of lists of incident faces (adjacency list)
 @param[out] VI  #V list of lists of index of incidence within incident faces listed
     in VF)"
    );
}




