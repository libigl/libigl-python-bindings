#include <npe.h>
#include <typedefs.h>






#include <igl/order_facets_around_edge.h>

const char* ds_order_facets_around_edge = R"igl_Qu8mg5v7(

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

 Given a directed edge, sort its adjacent faces.  Assuming the
       directed edge is (s, d).  Sort the adjacent faces clockwise around the
       axis (d - s), i.e. left-hand rule.  An adjacent face is consistently
       oriented if it contains (d, s) as a directed edge.
      
       For overlapping faces, break the tie using signed face index, smaller
       signed index comes before the larger signed index.  Signed index is
       computed as (consistent? 1:-1) * (face_index + 1).
      
       Inputs:
         V  #V by 3 list of vertices.
         F  #F by 3 list of faces
         s  Index of source vertex.
         d  Index of destination vertex.
         adj_faces  List of adjacent face signed indices.
       Output:
         order  List of face indices that orders adjacent faces around edge
           (s, d) clockwise.
)igl_Qu8mg5v7";

npe_function(order_facets_around_edge)
npe_doc(ds_order_facets_around_edge)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(adj_faces, std::vector<int> &)


npe_begin_code()

  size_t s;
  size_t d;
  EigenDense<npe_Scalar_> order;
  bool debug;
  igl::  copyleft::  cgal::order_facets_around_edge(v, f, adj_faces, s, d, order, debug);
  return std::make_tuple(npe::move(s), npe::move(d), npe::move(order), npe::move(debug));

npe_end_code()
#include <igl/order_facets_around_edge.h>

const char* ds_order_facets_around_edge = R"igl_Qu8mg5v7(

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

 This function is a wrapper around the one above.  Since the ordering
       is circular, the pivot point is used to define a starting point.  So
       order[0] is the index into adj_face that is immediately after the
       pivot face (s, d, pivot point) in clockwise order.
)igl_Qu8mg5v7";

npe_function(order_facets_around_edge)
npe_doc(ds_order_facets_around_edge)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(adj_faces, std::vector<int> &)
npe_arg(pivot_point, dense_float, dense_double)


npe_begin_code()

  size_t s;
  size_t d;
  EigenDense<npe_Scalar_> order;
  igl::  copyleft::  cgal::order_facets_around_edge(v, f, adj_faces, pivot_point, s, d, order);
  return std::make_tuple(npe::move(s), npe::move(d), npe::move(order));

npe_end_code()


