//TODO: __example

#include <npe.h>
#include <typedefs.h>
#include <igl/isolines.h>

const char *ds_isolines = R"igl_Qu8mg5v7(
 Constructs isolines for a function z given on a mesh (V,F)

Parameters
----------
       V  #V by dim list of mesh vertex positions
       F  #F by 3 list of mesh faces (must be triangles)
       z  #V by 1 list of function values evaluated at vertices
       n  the number of desired isolines

Returns
-------
       isoV  #isoV by dim list of isoline vertex positions
       isoE  #isoE by 2 list of isoline edge positions

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(isolines)
npe_doc(ds_isolines)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(z, dense_float, dense_double)
npe_arg(n, int)


npe_begin_code()

  npe_Matrix_v iso_v;
  npe_Matrix_f iso_e;
  igl::isolines(v, f, z, n, iso_v, iso_e);
  return std::make_tuple(npe::move(iso_v), npe::move(iso_e));

npe_end_code()


