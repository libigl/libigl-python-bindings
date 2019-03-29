#include <npe.h>
#include <typedefs.h>
#include <igl/snap_points.h>

const char* ds_snap_points = R"igl_Qu8mg5v7(

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

 SNAP_POINTS snap list of points C to closest of another list of points V
  
   [I,minD,VI] = snap_points(C,V)
   
   Inputs:
     C  #C by dim list of query point positions
     V  #V by dim list of data point positions
   Outputs:
     I  #C list of indices into V of closest points to C
     minD  #C list of squared (^p) distances to closest points
     VI  #C by dim list of new point positions, VI = V(I,:)
)igl_Qu8mg5v7";

npe_function(snap_points)
npe_doc(ds_snap_points)

npe_arg(c, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> min_d;
  EigenDense<npe_Scalar_> vi;
  igl::snap_points(c, v, i, min_d, vi);
  return std::make_tuple(npe::move(i), npe::move(min_d), npe::move(vi));

npe_end_code()
#include <igl/snap_points.h>

const char* ds_snap_points = R"igl_Qu8mg5v7(
See snap_points for the documentation.
)igl_Qu8mg5v7";

npe_function(snap_points)
npe_doc(ds_snap_points)

npe_arg(c, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> min_d;
  igl::snap_points(c, v, i, min_d);
  return std::make_tuple(npe::move(i), npe::move(min_d));

npe_end_code()
#include <igl/snap_points.h>

const char* ds_snap_points = R"igl_Qu8mg5v7(
See snap_points for the documentation.
)igl_Qu8mg5v7";

npe_function(snap_points)
npe_doc(ds_snap_points)

npe_arg(c, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> i;
  igl::snap_points(c, v, i);
  return npe::move(i);

npe_end_code()


