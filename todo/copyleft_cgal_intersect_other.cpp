#include <npe.h>
#include <typedefs.h>






#include <igl/intersect_other.h>

const char* ds_intersect_other = R"igl_Qu8mg5v7(

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

 INTERSECT_OTHER Given a triangle mesh (VA,FA) and another mesh (VB,FB)
       find all pairs of intersecting faces. Note that self-intersections are
       ignored.
       
       Inputs:
         VA  #V by 3 list of vertex positions
         FA  #F by 3 list of triangle indices into VA
         VB  #V by 3 list of vertex positions
         FB  #F by 3 list of triangle indices into VB
         params   whether to detect only and then whether to only find first
           intersection
       Outputs:
         IF  #intersecting face pairs by 2 list of intersecting face pairs,
           indexing FA and FB
         VVAB  #VVAB by 3 list of vertex positions
         FFAB  #FFAB by 3 list of triangle indices into VVA
         JAB  #FFAB list of indices into [FA;FB] denoting birth triangle
         IMAB  #VVAB list of indices stitching duplicates (resulting from
           mesh intersections) together
)igl_Qu8mg5v7";

npe_function(intersect_other)
npe_doc(ds_intersect_other)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)
npe_arg(params, igl::copyleft::cgal::RemeshSelfIntersectionsParam &)


npe_begin_code()

  EigenDense<npe_Scalar_> if;
  EigenDense<npe_Scalar_> vvab;
  EigenDense<npe_Scalar_> ffab;
  EigenDense<npe_Scalar_> jab;
  EigenDense<npe_Scalar_> imab;
  igl::  copyleft::  cgal::intersect_other(va, fa, vb, fb, params, if, vvab, ffab, jab, imab);
  return std::make_tuple(npe::move(if), npe::move(vvab), npe::move(ffab), npe::move(jab), npe::move(imab));

npe_end_code()
#include <igl/intersect_other.h>

const char* ds_intersect_other = R"igl_Qu8mg5v7(

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

 Legacy wrapper for detect only using common types.
      
       Inputs:
         VA  #V by 3 list of vertex positions
         FA  #F by 3 list of triangle indices into VA
         VB  #V by 3 list of vertex positions
         FB  #F by 3 list of triangle indices into VB
         first_only  whether to only detect the first intersection.
       Outputs:
         IF  #intersecting face pairs by 2 list of intersecting face pairs,
           indexing FA and FB
       Returns true if any intersections were found
      
       See also: remesh_self_intersections
)igl_Qu8mg5v7";

npe_function(intersect_other)
npe_doc(ds_intersect_other)

npe_arg(va, Eigen::MatrixXd &)
npe_arg(fa, Eigen::MatrixXi &)
npe_arg(vb, Eigen::MatrixXd &)
npe_arg(fb, Eigen::MatrixXi &)
npe_arg(first_only, bool)


npe_begin_code()

  Eigen::MatrixXi & if;
  igl::  copyleft::  cgal::intersect_other(va, fa, vb, fb, first_only, if);
  return npe::move(if);

npe_end_code()


