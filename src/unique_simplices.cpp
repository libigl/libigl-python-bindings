#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/unique_simplices.h>

const char *ds_unique_simplices = R"igl_Qu8mg5v7(
Find *combinatorially* unique simplices in F.  **Order independent**
Parameters
----------
F  #F by simplex-size list of simplices

Returns
-------
    FF  #FF by simplex-size list of unique simplices in F
    IA  #FF index vector so that FF == sort(F(IA,:),2);
    IC  #F index vector so that sort(F,2) == FF(IC,:);

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(unique_simplices)
npe_doc(ds_unique_simplices)

npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_valid_tet_or_tri_mesh_faces(f);

  EigenDenseLike<npe_Matrix_f> ff;
  EigenDenseLike<npe_Matrix_f> ia;
  EigenDenseLike<npe_Matrix_f> ic;
  igl::unique_simplices(f, ff, ia, ic);
  return std::make_tuple(npe::move(ff), npe::move(ia), npe::move(ic));

npe_end_code()


