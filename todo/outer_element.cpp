#include <npe.h>
#include <typedefs.h>






#include <igl/outer_vertex.h>

const char* ds_outer_vertex = R"igl_Qu8mg5v7(

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

 Find a vertex that is reachable from infinite without crossing any faces.
   Such vertex is called "outer vertex."
  
   Precondition: The input mesh must have all self-intersection resolved and
   no duplicated vertices.  See cgal::remesh_self_intersections.h for how to
   obtain such input.
  
   Inputs:
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices into V
     I  #I list of facets to consider
   Outputs:
     v_index  index of outer vertex
     A  #A list of facets incident to the outer vertex
)igl_Qu8mg5v7";

npe_function(outer_vertex)
npe_doc(ds_outer_vertex)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(i, dense_f32, dense_f64)


npe_begin_code()

  IndexType & v_index;
  EigenDense<npe_Scalar_> a;
  igl::outer_vertex(v, f, i, v_index, a);
  return std::make_tuple(npe::move(v_index), npe::move(a));

npe_end_code()
#include <igl/outer_edge.h>

const char* ds_outer_edge = R"igl_Qu8mg5v7(

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

 Find an edge that is reachable from infinity without crossing any faces.
   Such edge is called "outer edge."
  
   Precondition: The input mesh must have all self-intersection resolved and
   no duplicated vertices.  The correctness of the output depends on the fact
   that there is no edge overlap.  See cgal::remesh_self_intersections.h for
   how to obtain such input.
  
   Inputs:
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices into V
     I  #I list of facets to consider
   Outputs:
     v1 index of the first end point of outer edge
     v2 index of the second end point of outer edge
     A  #A list of facets incident to the outer edge
)igl_Qu8mg5v7";

npe_function(outer_edge)
npe_doc(ds_outer_edge)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(i, dense_f32, dense_f64)


npe_begin_code()

  IndexType & v1;
  IndexType & v2;
  EigenDense<npe_Scalar_> a;
  igl::outer_edge(v, f, i, v1, v2, a);
  return std::make_tuple(npe::move(v1), npe::move(v2), npe::move(a));

npe_end_code()
#include <igl/outer_facet.h>

const char* ds_outer_facet = R"igl_Qu8mg5v7(

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

 Find a facet that is reachable from infinity without crossing any faces.
   Such facet is called "outer facet."
  
   Precondition: The input mesh must have all self-intersection resolved.  I.e
   there is no duplicated vertices, no overlapping edge and no intersecting
   faces (the only exception is there could be topologically duplicated faces).
   See cgal::remesh_self_intersections.h for how to obtain such input.
  
   Inputs:
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices into V
     N  #N by 3 list of face normals
     I  #I list of facets to consider
   Outputs:
     f  Index of the outer facet.
     flipped  true iff the normal of f points inwards.
)igl_Qu8mg5v7";

npe_function(outer_facet)
npe_doc(ds_outer_facet)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(n, dense_f32, dense_f64)
npe_arg(i, dense_f32, dense_f64)


npe_begin_code()

  IndexType & f;
  bool & flipped;
  igl::outer_facet(v, f, n, i, f, flipped);
  return std::make_tuple(npe::move(f), npe::move(flipped));

npe_end_code()


