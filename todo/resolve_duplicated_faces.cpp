#include <npe.h>
#include <typedefs.h>
#include <igl/resolve_duplicated_faces.h>

const char* ds_resolve_duplicated_faces = R"igl_Qu8mg5v7(

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

 Resolve duplicated faces according to the following rules per unique face:
  
   1. If the number of positively oriented faces equals the number of
      negatively oriented faces, remove all duplicated faces at this triangle.
   2. If the number of positively oriented faces equals the number of
      negatively oriented faces plus 1, keeps one of the positively oriented
      face.
   3. If the number of positively oriented faces equals the number of
      negatively oriented faces minus 1, keeps one of the negatively oriented
      face.
   4. If the number of postively oriented faces differ with the number of
      negativley oriented faces by more than 1, the mesh is not orientable.
      An exception will be thrown.
  
   Inputs:
     F1  #F1 by 3 array of input faces.
  
   Outputs:
     F2  #F2 by 3 array of output faces without duplicated faces.
     J   #F2 list of indices into F1.
)igl_Qu8mg5v7";

npe_function(resolve_duplicated_faces)
npe_doc(ds_resolve_duplicated_faces)

npe_arg(f1, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> f2;
  EigenDense<npe_Scalar_> j;
  igl::resolve_duplicated_faces(f1, f2, j);
  return std::make_tuple(npe::move(f2), npe::move(j));

npe_end_code()


