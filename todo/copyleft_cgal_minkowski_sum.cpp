#include <npe.h>
#include <typedefs.h>
#include <igl/minkowski_sum.h>

const char* ds_minkowski_sum = R"igl_Qu8mg5v7(

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

 Compute the Minkowski sum of a closed triangle mesh (V,F) and a
       set of simplices in 3D.
      
       Inputs:
         VA  #VA by 3 list of mesh vertices in 3D
         FA  #FA by 3 list of triangle indices into VA
         VB  #VB by 3 list of mesh vertices in 3D
         FB  #FB by ss list of simplex indices into VB, ss<=3
         resolve_overlaps  whether or not to resolve self-union. If false
           then result may contain self-intersections if input mesh is
           non-convex.
       Outputs:
         W  #W by 3 list of mesh vertices in 3D
         G  #G by 3 list of triangle indices into W
         J  #G by 2 list of indices into 
         
)igl_Qu8mg5v7";

npe_function(minkowski_sum)
npe_doc(ds_minkowski_sum)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)
npe_arg(resolve_overlaps, bool)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  EigenDense<npe_Scalar_> g;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::minkowski_sum(va, fa, vb, fb, resolve_overlaps, w, g, j);
  return std::make_tuple(npe::move(w), npe::move(g), npe::move(j));

npe_end_code()






#include <igl/minkowski_sum.h>

const char* ds_minkowski_sum = R"igl_Qu8mg5v7(

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

 Compute the Minkowski sum of a closed triangle mesh (V,F) and a
       segment [s,d] in 3D.
      
       Inputs:
         VA  #VA by 3 list of mesh vertices in 3D
         FA  #FA by 3 list of triangle indices into VA
         s  segment source endpoint in 3D
         d  segment source endpoint in 3D
         resolve_overlaps  whether or not to resolve self-union. If false
           then result may contain self-intersections if input mesh is
           non-convex.
       Outputs:
         W  #W by 3 list of mesh vertices in 3D
         G  #G by 3 list of triangle indices into W
         J  #G list of indices into [F;#V+F;[s d]] of birth parents
      
)igl_Qu8mg5v7";

npe_function(minkowski_sum)
npe_doc(ds_minkowski_sum)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(s, Eigen::Matrix<sType, 1, sCols, sOptions> &)
npe_arg(d, Eigen::Matrix<dType, 1, dCols, dOptions> &)
npe_arg(resolve_overlaps, bool)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  EigenDense<npe_Scalar_> g;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::minkowski_sum(va, fa, s, d, resolve_overlaps, w, g, j);
  return std::make_tuple(npe::move(w), npe::move(g), npe::move(j));

npe_end_code()
#include <igl/minkowski_sum.h>

const char* ds_minkowski_sum = R"igl_Qu8mg5v7(
See minkowski_sum for the documentation.
)igl_Qu8mg5v7";

npe_function(minkowski_sum)
npe_doc(ds_minkowski_sum)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(s, Eigen::Matrix<sType, 1, sCols, sOptions> &)
npe_arg(d, Eigen::Matrix<dType, 1, dCols, dOptions> &)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  EigenDense<npe_Scalar_> g;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::minkowski_sum(va, fa, s, d, w, g, j);
  return std::make_tuple(npe::move(w), npe::move(g), npe::move(j));

npe_end_code()


