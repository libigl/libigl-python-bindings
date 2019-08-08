#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/circumradius.h>

const char* ds_circumradius = R"igl_Qu8mg5v7(

Compute the circumradius of each triangle in a mesh (V,F)
Parameters
----------
V  #V by dim list of mesh vertex positions
F  #F by 3 list of triangle indices into V
 

Returns
-------
R  #F list of circumradii

See also
--------


Notes
-----
None

Examples
--------
R = circumradius(V, F)
  
  
)igl_Qu8mg5v7";

npe_function(circumradius)
npe_doc(ds_circumradius)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  EigenDense<npe_Scalar_v> r;
  igl::circumradius(v, f, r);
  return npe::move(r);

npe_end_code()


