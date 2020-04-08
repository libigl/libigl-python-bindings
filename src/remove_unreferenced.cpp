// TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/remove_unreferenced.h>

const char* ds_remove_unreferenced = R"igl_Qu8mg5v7(

Remove unreferenced vertices from V, updating F accordingly

Parameters
----------
V  #V by dim list of mesh vertex positions
F  #F by ss list of simplices (Values of -1 are quitely skipped)


Returns
-------
NV  #NV by dim list of mesh vertex positions
NF  #NF by ss list of simplices
IM  #V by 1 list of indices such that: NF = IM(F) and NT = IM(T)
  and V(find(IM<=size(NV,1)),:) = NV
J  #RV by 1 list, such that RV = V(J,:)


See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(remove_unreferenced)
npe_doc(ds_remove_unreferenced)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  EigenDenseLike<npe_Matrix_v> nv;
  EigenDenseLike<npe_Matrix_f> nf, i, j;
  igl::remove_unreferenced(v, f, nv, nf, i, j);
  return std::make_tuple(npe::move(nv), npe::move(nf), npe::move(i), npe::move(j));

npe_end_code()

