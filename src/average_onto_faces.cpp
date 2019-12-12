#include <common.h>
#include <npe.h>
#include <typedefs.h>

const char* doccc_faces_avg = R"igl_Qu8mg5v7(
Move a scalar field defined on vertices to faces by averaging

Parameters
----------
f : #f by ss list of simplexes/faces
s : #v by dim list of per-vertex values

Returns
-------
#f by dim list of per-face values

See also
--------
average_onto_vertices

Notes
-----

Examples
--------
)igl_Qu8mg5v7";

npe_function(average_onto_faces)
npe_doc(doccc_faces_avg)

npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(s, dense_float, dense_double)


npe_begin_code()
  assert_valid_tet_or_tri_mesh_faces(f);
  //TODO: wierd behavior
  EigenDenseLike<npe_Matrix_s> SF;
  SF.setConstant(f.rows(), s.cols(), 0);
  for (int i = 0; i < f.rows(); ++i)
    for (int j = 0; j < f.cols(); ++j)
      SF.row(i) += s.row(f(i, j));
  SF.array() /= s.cols();
  return npe::move(SF);

npe_end_code()

