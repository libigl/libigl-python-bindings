#include <npe.h>
#include <typedefs.h>






#include <igl/point_mesh_squared_distance.h>

const char* ds_point_mesh_squared_distance = R"igl_Qu8mg5v7(

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

 Compute distances from a set of points P to a triangle mesh (V,F)
  
   Inputs:
     P  #P by 3 list of query point positions
     V  #V by 3 list of vertex positions
     Ele  #Ele by (3|2|1) list of (triangle|edge|point) indices
   Outputs:
     sqrD  #P list of smallest squared distances
     I  #P list of primitive indices corresponding to smallest distances
     C  #P by 3 list of closest points
  
   Known bugs: This only computes distances to given primitivess. So
   unreferenced vertices are ignored. However, degenerate primitives are
   handled correctly: triangle [1 2 2] is treated as a segment [1 2], and
   triangle [1 1 1] is treated as a point. So one _could_ add extra
   combinatorially degenerate rows to Ele for all unreferenced vertices to
   also get distances to points.
)igl_Qu8mg5v7";

npe_function(point_mesh_squared_distance)
npe_doc(ds_point_mesh_squared_distance)

npe_arg(p, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)
npe_arg(ele, Eigen::MatrixXi &)


npe_begin_code()

  EigenDense<npe_Scalar_> sqr_d;
  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> c;
  igl::point_mesh_squared_distance(p, v, ele, sqr_d, i, c);
  return std::make_tuple(npe::move(sqr_d), npe::move(i), npe::move(c));

npe_end_code()


