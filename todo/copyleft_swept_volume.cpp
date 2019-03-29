#include <npe.h>
#include <typedefs.h>






#include <igl/swept_volume.h>

const char* ds_swept_volume = R"igl_Qu8mg5v7(

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

 Compute the surface of the swept volume of a solid object with surface
     (V,F) mesh under going rigid motion.
     
     Inputs:
       V  #V by 3 list of mesh positions in reference pose
       F  #F by 3 list of mesh indices into V
       transform  function handle so that transform(t) returns the rigid
         transformation at time t∈[0,1]
       steps  number of time steps: steps=3 --> t∈{0,0.5,1}
       grid_res  number of grid cells on the longest side containing the
         motion (isolevel+1 cells will also be added on each side as padding)
       isolevel  distance level to be contoured as swept volume
     Outputs:
       SV  #SV by 3 list of mesh positions of the swept surface
       SF  #SF by 3 list of mesh faces into SV
)igl_Qu8mg5v7";

npe_function(swept_volume)
npe_doc(ds_swept_volume)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(transform, std::function<Eigen::Affine3d (const double)> &)
npe_arg(steps, size_t)
npe_arg(grid_res, size_t)
npe_arg(isolevel, size_t)


npe_begin_code()

  Eigen::MatrixXd & sv;
  Eigen::MatrixXi & sf;
  igl::  copyleft::swept_volume(v, f, transform, steps, grid_res, isolevel, sv, sf);
  return std::make_tuple(npe::move(sv), npe::move(sf));

npe_end_code()


