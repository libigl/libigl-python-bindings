#include <npe.h>
#include <typedefs.h>
#include <igl/iterative_closest_point.h>

const char* ds_iterative_closest_point = R"igl_Qu8mg5v7(

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

 Solve for the rigid transformation that places mesh X onto mesh Y using the
   iterative closest point method. In particular, optimize:
  
   min      ∫_X inf ‖x*R+t - y‖² dx
   R∈SO(3)      y∈Y
   t∈R³
  
   Typically optimization strategies include using Gauss Newton
   ("point-to-plane" linearization) and stochastic descent (sparse random
   sampling each iteration).
  
   Inputs:
     VX  #VX by 3 list of mesh X vertices
     FX  #FX by 3 list of mesh X triangle indices into rows of VX
     VY  #VY by 3 list of mesh Y vertices
     FY  #FY by 3 list of mesh Y triangle indices into rows of VY
     num_samples  number of random samples to use (larger --> more accurate,
       but also more suceptible to sticking to local minimum)
   Outputs:
     R  3x3 rotation matrix so that (VX*R+t,FX) ~~ (VY,FY)
     t  1x3 translation row vector
)igl_Qu8mg5v7";

npe_function(iterative_closest_point)
npe_doc(ds_iterative_closest_point)

npe_arg(vx, dense_f32, dense_f64)
npe_arg(fx, dense_f32, dense_f64)
npe_arg(vy, dense_f32, dense_f64)
npe_arg(fy, dense_f32, dense_f64)
npe_arg(num_samples, int)
npe_arg(max_iters, int)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  EigenDense<npe_Scalar_> t;
  igl::iterative_closest_point(vx, fx, vy, fy, num_samples, max_iters, r, t);
  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()






#include <igl/iterative_closest_point.h>

const char* ds_iterative_closest_point = R"igl_Qu8mg5v7(

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

 Inputs:
     Ytree  precomputed AABB tree for accelerating closest point queries
     NY  #FY by 3 list of precomputed unit face normals
)igl_Qu8mg5v7";

npe_function(iterative_closest_point)
npe_doc(ds_iterative_closest_point)

npe_arg(vx, dense_f32, dense_f64)
npe_arg(fx, dense_f32, dense_f64)
npe_arg(vy, dense_f32, dense_f64)
npe_arg(fy, dense_f32, dense_f64)
npe_arg(ytree, igl::AABB<DerivedVY, 3> &)
npe_arg(ny, dense_f32, dense_f64)
npe_arg(num_samples, int)
npe_arg(max_iters, int)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  EigenDense<npe_Scalar_> t;
  igl::iterative_closest_point(vx, fx, vy, fy, ytree, ny, num_samples, max_iters, r, t);
  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()


