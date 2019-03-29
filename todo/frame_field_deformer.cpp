#include <npe.h>
#include <typedefs.h>






#include <igl/frame_field_deformer.h>

const char* ds_frame_field_deformer = R"igl_Qu8mg5v7(

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

 Deform a mesh to transform the given per-face frame field to be as close
   as possible to a cross field, in the least square sense.
  
   Inputs:
     V       #V by 3 coordinates of the vertices
     F       #F by 3 list of mesh faces (must be triangles)
     FF1     #F by 3 first representative vector of the frame field
     FF2     #F by 3 second representative vector of the frame field
     lambda  laplacian regularization parameter 0=no regularization 1=full regularization
  
   Outputs:
     V_d     #F by 3 deformed, first representative vector
     V_d     #F by 3 deformed, first representative vector
     V_d     #F by 3 deformed, first representative vector
  
)igl_Qu8mg5v7";

npe_function(frame_field_deformer)
npe_doc(ds_frame_field_deformer)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(ff1, Eigen::MatrixXd &)
npe_arg(ff2, Eigen::MatrixXd &)
npe_arg(iterations, int)
npe_arg(lambda, double)
npe_arg(perturb_initial_guess, bool)


npe_begin_code()

  Eigen::MatrixXd & v_d;
  Eigen::MatrixXd & ff1_d;
  Eigen::MatrixXd & ff2_d;
  igl::frame_field_deformer(v, f, ff1, ff2, iterations, lambda, perturb_initial_guess, v_d, ff1_d, ff2_d);
  return std::make_tuple(npe::move(v_d), npe::move(ff1_d), npe::move(ff2_d));

npe_end_code()


