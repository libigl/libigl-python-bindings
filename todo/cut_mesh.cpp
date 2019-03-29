#include <npe.h>
#include <typedefs.h>
#include <igl/cut_mesh.h>

const char* ds_cut_mesh = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

Wrapper of the above with only vertices and faces as mesh input
)igl_Qu8mg5v7";

npe_function(cut_mesh)
npe_doc(ds_cut_mesh)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(cuts, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> vcut;
  EigenDense<npe_Scalar_> fcut;
  igl::cut_mesh(v, f, cuts, vcut, fcut);
  return std::make_tuple(npe::move(vcut), npe::move(fcut));

npe_end_code()






#include <igl/cut_mesh.h>

const char* ds_cut_mesh = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Given a mesh and a list of edges that are to be cut, the function
   generates a new disk-topology mesh that has the cuts at its boundary.
  
   Todo: this combinatorial operation should not depend on the vertex
   positions V.
  
   Known issues: Assumes mesh is edge-manifold.
  
   Inputs:
     V  #V by 3 list of the vertex positions
     F  #F by 3 list of the faces (must be triangles)
     VF  #V list of lists of incident faces (adjacency list), e.g.  as
       returned by igl::vertex_triangle_adjacency
     VFi  #V list of lists of index of incidence within incident faces listed
       in VF, e.g. as returned by igl::vertex_triangle_adjacency
     TT  #F by 3 triangle to triangle adjacent matrix (e.g. computed via
       igl:triangle_triangle_adjacency)
     TTi  #F by 3 adjacent matrix, the element i,j is the id of edge of the
       triangle TT(i,j) that is adjacent with triangle i (e.g. computed via
       igl:triangle_triangle_adjacency)
     V_border  #V by 1 list of booleans, indicating if the corresponging
       vertex is at the mesh boundary, e.g. as returned by
       igl::is_border_vertex
     cuts  #F by 3 list of boolean flags, indicating the edges that need to
       be cut (has 1 at the face edges that are to be cut, 0 otherwise)
   Outputs:
     Vcut  #V by 3 list of the vertex positions of the cut mesh. This matrix
       will be similar to the original vertices except some rows will be
       duplicated.
     Fcut  #F by 3 list of the faces of the cut mesh(must be triangles). This
       matrix will be similar to the original face matrix except some indices
       will be redirected to point to the newly duplicated vertices.
  
)igl_Qu8mg5v7";

npe_function(cut_mesh)
npe_doc(ds_cut_mesh)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(vf, std::vector<std::vector<VFType> > &)
npe_arg(v_fi, std::vector<std::vector<VFType> > &)
npe_arg(tt, dense_f32, dense_f64)
npe_arg(t_ti, dense_f32, dense_f64)
npe_arg(v_border, std::vector<bool> &)
npe_arg(cuts, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> vcut;
  EigenDense<npe_Scalar_> fcut;
  igl::cut_mesh(v, f, vf, v_fi, tt, t_ti, v_border, cuts, vcut, fcut);
  return std::make_tuple(npe::move(vcut), npe::move(fcut));

npe_end_code()


