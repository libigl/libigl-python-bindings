#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/resolve_duplicated_faces.h>

const char* ds_resolve_duplicated_faces = R"igl_Qu8mg5v7(

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

Parameters
----------
F1  #F1 by 3 array of input faces.

Returns
-------
F2  #F2 by 3 array of output faces without duplicated faces.
J   #F2 list of indices into F1.

See also
--------


Notes
-----
None

Examples
--------
  
  
)igl_Qu8mg5v7";

npe_function(resolve_duplicated_faces)
npe_doc(ds_resolve_duplicated_faces)

npe_arg(f1, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_tri_mesh_faces(f1, "f1");
  // TODO: remove __copy
  // same problem that DerivedF1 causes problem, can be prevented
  Eigen::MatrixXi f1_copy = f1.template cast<int>();
  EigenDenseLike<npe_Matrix_f1> f2, j;
  igl::resolve_duplicated_faces(f1_copy, f2, j);
  return std::make_tuple(npe::move(f2), npe::move(j));

npe_end_code()


