#include <npe.h>
#include <typedefs.h>
#include <igl/trim_with_solid.h>

const char* ds_trim_with_solid = R"igl_Qu8mg5v7(

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

 TRIM_WITH_SOLID Given an arbitrary mesh (VA,FA) and the boundary mesh
       (VB,FB) of a solid (as defined in [Zhou et al. 2016]), Resolve intersections
       between A and B subdividing faces of A so that intersections with B exists
       only along edges and vertices (and coplanar faces). Then determine whether
       each of these faces is inside or outside of B. This can be used to extract
       the part of A inside or outside of B.
      
       Inputs:
         VA  #VA by 3 list of mesh vertex positions of A
         FA  #FA by 3 list of mesh triangle indices into VA
         VB  #VB by 3 list of mesh vertex positions of B
         FB  #FB by 3 list of mesh triangle indices into VB
       Outputs:
         V  #V by 3 list of mesh vertex positions of output
         F  #F by 3 list of mesh triangle indices into V
         D  #F list of bools whether face is inside B
         J  #F list of indices into FA revealing birth parent
      
)igl_Qu8mg5v7";

npe_function(trim_with_solid)
npe_doc(ds_trim_with_solid)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> vd;
  EigenDense<npe_Scalar_> f;
  EigenDense<npe_Scalar_> d;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::trim_with_solid(va, fa, vb, fb, vd, f, d, j);
  return std::make_tuple(npe::move(vd), npe::move(f), npe::move(d), npe::move(j));

npe_end_code()


