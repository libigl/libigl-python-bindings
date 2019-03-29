#include <npe.h>
#include <typedefs.h>






#include <igl/extract_non_manifold_edge_curves.h>

const char* ds_extract_non_manifold_edge_curves = R"igl_Qu8mg5v7(

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

 Extract non-manifold curves from a given mesh.
     A non-manifold curves are a set of connected non-manifold edges that
     does not touch other non-manifold edges except at the end points.
     They are also maximal in the sense that they cannot be expanded by
     including more edges.
    
     Assumes the input mesh have all self-intersection resolved.  See
     ``igl::cgal::remesh_self_intersection`` for more details.
    
     Inputs:
       F  #F by 3 list representing triangles.
       EMAP  #F*3 list of indices of unique undirected edges.
       uE2E  #uE list of lists of indices into E of coexisting edges.
    
     Output:
       curves  An array of arries of unique edge indices.
)igl_Qu8mg5v7";

npe_function(extract_non_manifold_edge_curves)
npe_doc(ds_extract_non_manifold_edge_curves)

npe_arg(f, dense_i32, dense_i64)
npe_arg(emap, dense_f32, dense_f64)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)


npe_begin_code()

  std::vector<std::vector<size_t> > & curves;
  igl::extract_non_manifold_edge_curves(f, emap, u_e2_e, curves);
  return npe::move(curves);

npe_end_code()


