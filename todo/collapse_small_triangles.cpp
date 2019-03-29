#include <npe.h>
#include <typedefs.h>






#include <igl/collapse_small_triangles.h>

const char* ds_collapse_small_triangles = R"igl_Qu8mg5v7(

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

 Given a triangle mesh (V,F) compute a new mesh (VV,FF) which contains the
   original faces and vertices of (V,F) except any small triangles have been
   removed via collapse.
  
   We are *not* following the rules in "Mesh Optimization" [Hoppe et al]
   Section 4.2. But for our purposes we don't care about this criteria.
  
   Inputs:
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices into V
     eps  epsilon for smallest allowed area treated as fraction of squared bounding box
       diagonal
   Outputs:
     FF  #FF by 3 list of triangle indices into V
  
  
)igl_Qu8mg5v7";

npe_function(collapse_small_triangles)
npe_doc(ds_collapse_small_triangles)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(eps, double)


npe_begin_code()

  Eigen::MatrixXi & ff;
  igl::collapse_small_triangles(v, f, eps, ff);
  return npe::move(ff);

npe_end_code()


