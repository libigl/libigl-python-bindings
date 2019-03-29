#include <npe.h>
#include <typedefs.h>






#include <igl/fit_plane.h>

const char* ds_fit_plane = R"igl_Qu8mg5v7(

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

 This function fits a plane to a point cloud.
  
   Input:
     V #Vx3 matrix. The 3D point cloud, one row for each vertex.
   Output: 
     N 1x3 Vector. The normal of the fitted plane.
     C 1x3 Vector. A point that lies in the fitted plane.
   From http:missingbytes.blogspot.com/2012/06/fitting-plane-to-point-cloud.html
)igl_Qu8mg5v7";

npe_function(fit_plane)
npe_doc(ds_fit_plane)

npe_arg(v, Eigen::MatrixXd &)


npe_begin_code()

  Eigen::RowVector3d & n;
  Eigen::RowVector3d & c;
  igl::fit_plane(v, n, c);
  return std::make_tuple(npe::move(n), npe::move(c));

npe_end_code()


