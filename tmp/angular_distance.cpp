// TODO: __type Quaterniond . missing __example

#include <npe.h>
#include <typedefs.h>






#include <igl/angular_distance.h>

const char* ds_angular_distance = R"igl_Qu8mg5v7(
 
The "angular distance" between two unit quaternions is the angle of the
  smallest rotation (treated as an Axis and Angle) that takes A to B.

Parameters
----------
A  unit quaternion
B  unit quaternion


Returns
-------
Returns angular distance

See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(angular_distance)
npe_doc(ds_angular_distance)

npe_arg(a, Eigen::Quaterniond &)
npe_arg(b, Eigen::Quaterniond &)


npe_begin_code()

  igl::angular_distance(a, b);
  return ;

npe_end_code()


