// TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/euler_characteristic.h>

const char* ds_euler_characteristic = R"igl_Qu8mg5v7(

Computes the Euler characteristic of a given mesh (V,F)

Parameters
----------
F #F by dim list of mesh faces (must be triangles)

Returns
-------
Returns An int containing the Euler characteristic

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(euler_characteristic)
npe_doc(ds_euler_characteristic)

npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_tri_mesh_faces(f);
  return igl::euler_characteristic(f);

npe_end_code()



