#include <npe.h>
#include <typedefs.h>
#include <igl/procrustes.h>

const char* ds_procrustes = R"igl_Qu8mg5v7(

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

 Convenient wrapper that returns S=scale*R instead of scale and R separately
)igl_Qu8mg5v7";

npe_function(procrustes)
npe_doc(ds_procrustes)

npe_arg(x, dense_f32, dense_f64)
npe_arg(y, dense_f32, dense_f64)


npe_begin_code()

  bool include_scaling;
  bool include_reflections;
  EigenDense<npe_Scalar_> s;
  EigenDense<npe_Scalar_> t;
  igl::procrustes(x, y, include_scaling, include_reflections, s, t);
  return std::make_tuple(npe::move(include_scaling), npe::move(include_reflections), npe::move(s), npe::move(t));

npe_end_code()
#include <igl/procrustes.h>

const char* ds_procrustes = R"igl_Qu8mg5v7(

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

 Convenient wrapper for rigid case (no scaling, no reflections)
)igl_Qu8mg5v7";

npe_function(procrustes)
npe_doc(ds_procrustes)

npe_arg(x, dense_f32, dense_f64)
npe_arg(y, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> r;
  EigenDense<npe_Scalar_> t;
  igl::procrustes(x, y, r, t);
  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()






#include <igl/procrustes.h>

const char* ds_procrustes = R"igl_Qu8mg5v7(

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

 Solve Procrustes problem in d dimensions.  Given two point sets X,Y in R^d
   find best scale s, orthogonal R  and translation t s.t. |s*X*R + t - Y|^2
   is minimized.
  
   Templates:
      DerivedV point type
      Scalar   scalar type
      DerivedR type of R
      DerivedT type of t
   Inputs:
      X  #V by DIM first list of points
      Y  #V by DIM second list of points
      includeScaling  if scaling should be allowed
      includeReflections  if R is allowed to be a reflection
   Outputs:
      scale  scaling
      R      orthogonal matrix
      t      translation
  
   Example:
     MatrixXd X, Y; (containing 3d points as rows)
     double scale;
     MatrixXd R;
     VectorXd t;
     igl::procrustes(X,Y,true,false,scale,R,t);
     R *= scale;
     MatrixXd Xprime = (X * R).rowwise() + t.transpose();
  
)igl_Qu8mg5v7";

npe_function(procrustes)
npe_doc(ds_procrustes)

npe_arg(x, dense_f32, dense_f64)
npe_arg(y, dense_f32, dense_f64)


npe_begin_code()

  bool include_scaling;
  bool include_reflections;
  Scalar & scale;
  EigenDense<npe_Scalar_> r;
  EigenDense<npe_Scalar_> t;
  igl::procrustes(x, y, include_scaling, include_reflections, scale, r, t);
  return std::make_tuple(npe::move(include_scaling), npe::move(include_reflections), npe::move(scale), npe::move(r), npe::move(t));

npe_end_code()
#include <igl/procrustes.h>

const char* ds_procrustes = R"igl_Qu8mg5v7(

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

 Same as above but returns Eigen transformation object.
  
   Templates:
      DerivedV point type
      Scalar   scalar type
      DIM      point dimension
      TType    type of transformation
               (Isometry,Affine,AffineCompact,Projective)
   Inputs:
      X  #V by DIM first list of points
      Y  #V by DIM second list of points
      includeScaling  if scaling should be allowed
      includeReflections  if R is allowed to be a reflection
   Outputs:
      T  transformation that minimizes error    
  
   Example:
     MatrixXd X, Y; (containing 3d points as rows)
     AffineCompact3d T;
     igl::procrustes(X,Y,true,false,T);
     MatrixXd Xprime = (X * T.linear()).rowwise() + T.translation().transpose();
)igl_Qu8mg5v7";

npe_function(procrustes)
npe_doc(ds_procrustes)

npe_arg(x, dense_f32, dense_f64)
npe_arg(y, dense_f32, dense_f64)


npe_begin_code()

  bool include_scaling;
  bool include_reflections;
  Eigen::Transform<Scalar, DIM, TType> & t;
  igl::procrustes(x, y, include_scaling, include_reflections, t);
  return std::make_tuple(npe::move(include_scaling), npe::move(include_reflections), npe::move(t));

npe_end_code()
#include <igl/procrustes.h>

const char* ds_procrustes = R"igl_Qu8mg5v7(

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

 Convenient wrapper for 2D case.
)igl_Qu8mg5v7";

npe_function(procrustes)
npe_doc(ds_procrustes)

npe_arg(x, dense_f32, dense_f64)
npe_arg(y, dense_f32, dense_f64)


npe_begin_code()

  Eigen::Rotation2D<Scalar> & r;
  EigenDense<npe_Scalar_> t;
  igl::procrustes(x, y, r, t);
  return std::make_tuple(npe::move(r), npe::move(t));

npe_end_code()


