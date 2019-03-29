#include <npe.h>
#include <typedefs.h>






#include <igl/swept_volume_signed_distance.h>

const char* ds_swept_volume_signed_distance = R"igl_Qu8mg5v7(

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

 Compute the signed distance to a sweep surface of a mesh under-going
   an arbitrary motion V(t) discretely sampled at `steps`-many moments in
   time at a grid.
  
   Inputs:
     V  #V by 3 list of mesh positions in reference pose
     F  #F by 3 list of triangle indices [0,n)
     transform  function handle so that transform(t) returns the rigid
       transformation at time t∈[0,1]
     steps  number of time steps: steps=3 --> t∈{0,0.5,1}
     GV  #GV by 3 list of evaluation point grid positions
     res  3-long resolution of GV grid
     h  edge-length of grid
     isolevel  isolevel to "focus" on; grid positions far enough away from
       isolevel (based on h) will get approximate values). Set
       isolevel=infinity to get good values everywhere (slow and
       unnecessary if just trying to extract isolevel-level set).
     S0  #GV initial values (will take minimum with these), can be same
       as S)
   Outputs:
     S  #GV list of signed distances
)igl_Qu8mg5v7";

npe_function(swept_volume_signed_distance)
npe_doc(ds_swept_volume_signed_distance)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(transform, std::function<Eigen::Affine3d (const double)> &)
npe_arg(steps, size_t &)
npe_arg(gv, Eigen::MatrixXd &)
npe_arg(res, Eigen::RowVector3i &)
npe_arg(h, double)
npe_arg(isolevel, double)
npe_arg(s0, Eigen::VectorXd &)


npe_begin_code()

  Eigen::VectorXd & s;
  igl::swept_volume_signed_distance(v, f, transform, steps, gv, res, h, isolevel, s0, s);
  return npe::move(s);

npe_end_code()
#include <igl/swept_volume_signed_distance.h>

const char* ds_swept_volume_signed_distance = R"igl_Qu8mg5v7(
See swept_volume_signed_distance for the documentation.
)igl_Qu8mg5v7";

npe_function(swept_volume_signed_distance)
npe_doc(ds_swept_volume_signed_distance)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(transform, std::function<Eigen::Affine3d (const double)> &)
npe_arg(steps, size_t &)
npe_arg(gv, Eigen::MatrixXd &)
npe_arg(res, Eigen::RowVector3i &)
npe_arg(h, double)
npe_arg(isolevel, double)


npe_begin_code()

  Eigen::VectorXd & s;
  igl::swept_volume_signed_distance(v, f, transform, steps, gv, res, h, isolevel, s);
  return npe::move(s);

npe_end_code()


