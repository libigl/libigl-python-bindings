#include <npe.h>
#include <typedefs.h>
#include <igl/shape_diameter_function.h>

const char* ds_shape_diameter_function = R"igl_Qu8mg5v7(

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
      V  #V by 3 list of mesh vertex positions
      F  #F by 3 list of mesh face indices into V
)igl_Qu8mg5v7";

npe_function(shape_diameter_function)
npe_doc(ds_shape_diameter_function)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(p, dense_f32, dense_f64)
npe_arg(n, dense_f32, dense_f64)
npe_arg(num_samples, int)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  igl::shape_diameter_function(v, f, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()
#include <igl/shape_diameter_function.h>

const char* ds_shape_diameter_function = R"igl_Qu8mg5v7(

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

   per_face  whether to compute per face (S is #F by 1) or per vertex (S is
       #V by 1)
)igl_Qu8mg5v7";

npe_function(shape_diameter_function)
npe_doc(ds_shape_diameter_function)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(per_face, bool)
npe_arg(num_samples, int)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  igl::shape_diameter_function(v, f, per_face, num_samples, s);
  return npe::move(s);

npe_end_code()






#include <igl/shape_diameter_function.h>

const char* ds_shape_diameter_function = R"igl_Qu8mg5v7(

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

 Compute shape diamater function per given point. In the parlence of the
   paper "Consistent Mesh Partitioning and Skeletonisation using the Shape
   Diameter Function" [Shapiro et al. 2008], this implementation uses a 180°
   cone and a _uniform_ average (_not_ a average weighted by inverse angles).
  
   Inputs:
      shoot_ray  function handle that outputs hits of a given ray against a
        mesh (embedded in function handles as captured variable/data)
      P  #P by 3 list of origin points
      N  #P by 3 list of origin normals
   Outputs:
      S  #P list of shape diamater function values between bounding box
      diagonal (perfect sphere) and 0 (perfect needle hook)
  
)igl_Qu8mg5v7";

npe_function(shape_diameter_function)
npe_doc(ds_shape_diameter_function)

npe_arg(shoot_ray, std::function<double (const Eigen::Vector3f &, const Eigen::Vector3f &)> &)
npe_arg(p, dense_f32, dense_f64)
npe_arg(n, dense_f32, dense_f64)
npe_arg(num_samples, int)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  igl::shape_diameter_function(shoot_ray, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()
#include <igl/shape_diameter_function.h>

const char* ds_shape_diameter_function = R"igl_Qu8mg5v7(

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
     AABB  axis-aligned bounding box hierarchy around (V,F)
)igl_Qu8mg5v7";

npe_function(shape_diameter_function)
npe_doc(ds_shape_diameter_function)

npe_arg(aabb, igl::AABB<DerivedV, DIM> &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(p, dense_f32, dense_f64)
npe_arg(n, dense_f32, dense_f64)
npe_arg(num_samples, int)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  igl::shape_diameter_function(aabb, v, f, p, n, num_samples, s);
  return npe::move(s);

npe_end_code()


