#include <npe.h>
#include <typedefs.h>
#include <igl/project_to_line.h>

const char* ds_project_to_line = R"igl_Qu8mg5v7(

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

 PROJECT_TO_LINE  project points onto vectors, that is find the parameter
   t for a point p such that proj_p = (y-x).*t, additionally compute the
   squared distance from p to the line of the vector, such that 
   |p - proj_p|² = sqr_d
  
   [T,sqrD] = project_to_line(P,S,D)
  
   Inputs:
     P  #P by dim list of points to be projected
     S  size dim start position of line vector
     D  size dim destination position of line vector
   Outputs:
     T  #P by 1 list of parameters
     sqrD  #P by 1 list of squared distances
  
  
)igl_Qu8mg5v7";

npe_function(project_to_line)
npe_doc(ds_project_to_line)

npe_arg(p, dense_f32, dense_f64)
npe_arg(s, dense_f32, dense_f64)
npe_arg(d, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> t;
  EigenDense<npe_Scalar_> sqr_d;
  igl::project_to_line(p, s, d, t, sqr_d);
  return std::make_tuple(npe::move(t), npe::move(sqr_d));

npe_end_code()






#include <igl/project_to_line.h>

const char* ds_project_to_line = R"igl_Qu8mg5v7(

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

 Same as above but for a single query point
)igl_Qu8mg5v7";

npe_function(project_to_line)
npe_doc(ds_project_to_line)

npe_arg(px, Scalar)
npe_arg(py, Scalar)
npe_arg(pz, Scalar)
npe_arg(sx, Scalar)
npe_arg(sy, Scalar)
npe_arg(sz, Scalar)
npe_arg(dx, Scalar)
npe_arg(dy, Scalar)
npe_arg(dz, Scalar)


npe_begin_code()

  Scalar & projpx;
  Scalar & projpy;
  Scalar & projpz;
  Scalar & t;
  Scalar & sqrd;
  igl::project_to_line(px, py, pz, sx, sy, sz, dx, dy, dz, projpx, projpy, projpz, t, sqrd);
  return std::make_tuple(npe::move(projpx), npe::move(projpy), npe::move(projpz), npe::move(t), npe::move(sqrd));

npe_end_code()
#include <igl/project_to_line.h>

const char* ds_project_to_line = R"igl_Qu8mg5v7(

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

 Same as above but for a single query point
)igl_Qu8mg5v7";

npe_function(project_to_line)
npe_doc(ds_project_to_line)

npe_arg(px, Scalar)
npe_arg(py, Scalar)
npe_arg(pz, Scalar)
npe_arg(sx, Scalar)
npe_arg(sy, Scalar)
npe_arg(sz, Scalar)
npe_arg(dx, Scalar)
npe_arg(dy, Scalar)
npe_arg(dz, Scalar)


npe_begin_code()

  Scalar & t;
  Scalar & sqrd;
  igl::project_to_line(px, py, pz, sx, sy, sz, dx, dy, dz, t, sqrd);
  return std::make_tuple(npe::move(t), npe::move(sqrd));

npe_end_code()


