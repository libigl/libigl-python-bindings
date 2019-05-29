#include <npe.h>
#include <typedefs.h>
#include <igl/sort_triangles.h>

const char* ds_sort_triangles = R"igl_Qu8mg5v7(

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
     V  #V by **4** list of homogeneous vertex positions
     F  #F by 3 list of triangle indices
     MV  4 by 4 model view matrix
     P  4 by 4 projection matrix
   Outputs:
     FF  #F by 3 list of sorted triangles indices
     I  #F list of sorted indices
)igl_Qu8mg5v7";

npe_function(sort_triangles)
npe_doc(ds_sort_triangles)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(mv, dense_float, dense_double)
npe_arg(p, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> i;
  igl::sort_triangles(v, f, mv, p, ff, i);
  return std::make_tuple(npe::move(ff), npe::move(i));

npe_end_code()


