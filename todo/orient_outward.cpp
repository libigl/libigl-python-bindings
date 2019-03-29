#include <npe.h>
#include <typedefs.h>
#include <igl/orient_outward.h>

const char* ds_orient_outward = R"igl_Qu8mg5v7(

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

 Orient each component (identified by C) of a mesh (V,F) so the normals on
   average point away from the patch's centroid.
  
   Inputs:
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices
     C  #F list of components (output of orientable_patches)
   Outputs:
     FF  #F by 3 list of new triangle indices such that FF(~I,:) = F(~I,:) and
       FF(I,:) = fliplr(F(I,:)) (OK if &FF = &F)
     I  max(C)+1 list of whether face has been flipped
)igl_Qu8mg5v7";

npe_function(orient_outward)
npe_doc(ds_orient_outward)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(c, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> i;
  igl::orient_outward(v, f, c, ff, i);
  return std::make_tuple(npe::move(ff), npe::move(i));

npe_end_code()


