#include <npe.h>
#include <typedefs.h>
#include <igl/intersect_with_half_space.h>

const char* ds_intersect_with_half_space = R"igl_Qu8mg5v7(

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

 Intersect a PWN mesh with a half-space. Point on plane, normal pointing
       outward.
      
       Inputs:
         V  #V by 3 list of mesh vertex positions
         p  3d point on plane
         n  3d vector of normal of plane pointing away from inside
       Outputs:
         VC  #VC by 3 list of vertex positions of boolean result mesh
         FC  #FC by 3 list of triangle indices into VC
         J  #FC list of indices into [F;F.rows()+[1;2]] revealing "birth"
           facet
)igl_Qu8mg5v7";

npe_function(intersect_with_half_space)
npe_doc(ds_intersect_with_half_space)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::intersect_with_half_space(v, f, p, n, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()
#include <igl/intersect_with_half_space.h>

const char* ds_intersect_with_half_space = R"igl_Qu8mg5v7(

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

 Intersect a PWN mesh with a half-space. Plane equation.
      
       Inputs:
         V  #V by 3 list of mesh vertex positions
         equ  plane equation: P(x,y,z) = a*x+b*y+c*z + d = 0, P(x,y,z) < 0 is
           _inside_.
       Outputs:
         VC  #VC by 3 list of vertex positions of boolean result mesh
         FC  #FC by 3 list of triangle indices into VC
         J  #FC list of indices into [F;F.rows()+[1;2]] revealing "birth" facet
)igl_Qu8mg5v7";

npe_function(intersect_with_half_space)
npe_doc(ds_intersect_with_half_space)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(equ, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::intersect_with_half_space(v, f, equ, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()






#include <igl/intersect_with_half_space.h>

const char* ds_intersect_with_half_space = R"igl_Qu8mg5v7(

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

 Intersect a PWN mesh with a half-space. CGAL Plane.
      
       Inputs:
         V  #V by 3 list of mesh vertex positions
         P  plane 
       Outputs:
         VC  #VC by 3 list of vertex positions of boolean result mesh
         FC  #FC by 3 list of triangle indices into VC
         J  #FC list of indices into [F;F.rows()+[1;2]] revealing "birth" facet
)igl_Qu8mg5v7";

npe_function(intersect_with_half_space)
npe_doc(ds_intersect_with_half_space)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(p, CGAL::Plane_3<CGAL::Epeck> &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::intersect_with_half_space(v, f, p, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()


