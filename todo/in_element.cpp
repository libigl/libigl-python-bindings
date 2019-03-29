#include <npe.h>
#include <typedefs.h>






#include <igl/in_element.h>

const char* ds_in_element = R"igl_Qu8mg5v7(

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

 Determine whether each point in a list of points is in the elements of a
   mesh.
  
   templates:
     DIM  dimension of vertices in V (# of columns)
   Inputs:
     V  #V by dim list of mesh vertex positions.
     Ele  #Ele by dim+1 list of mesh indices into #V.
     Q  #Q by dim list of query point positions
     aabb  axis-aligned bounding box tree object (see AABB.h)
   Outputs:
     I  #Q list of indices into Ele of first containing element (-1 means no
       containing element)
)igl_Qu8mg5v7";

npe_function(in_element)
npe_doc(ds_in_element)

npe_arg(v, dense_f32, dense_f64)
npe_arg(ele, Eigen::MatrixXi &)
npe_arg(q, dense_f32, dense_f64)
npe_arg(aabb, AABB<DerivedV, DIM> &)


npe_begin_code()

  Eigen::VectorXi & i;
  igl::in_element(v, ele, q, aabb, i);
  return npe::move(i);

npe_end_code()
#include <igl/in_element.h>

const char* ds_in_element = R"igl_Qu8mg5v7(

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

 Outputs:
     I  #Q by #Ele sparse matrix revealing whether each element contains each
       point: I(q,e) means point q is in element e
)igl_Qu8mg5v7";

npe_function(in_element)
npe_doc(ds_in_element)

npe_arg(v, dense_f32, dense_f64)
npe_arg(ele, Eigen::MatrixXi &)
npe_arg(q, dense_f32, dense_f64)
npe_arg(aabb, AABB<DerivedV, DIM> &)


npe_begin_code()

  Sparse_f64 i;
  igl::in_element(v, ele, q, aabb, i);
  return npe::move(i);

npe_end_code()


