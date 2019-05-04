#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/local_basis.h>

const char* ds_local_basis = R"igl_Qu8mg5v7(
Compute a local orthogonal reference system for each triangle in the given mesh.

Parameters
----------
v : #v by 3 vertex array
f : #f by 3 array of mesh faces (must be triangles)

Returns
-------
b1 : #f by 3 array, each vector is tangent to the triangle
b2 : #f by 3 array, each vector is tangent to the triangle and perpendicular to B1
b3 : #f by 3 array, normal of the triangle

See also
--------
adjacency_matrix

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(local_basis)
npe_doc(ds_local_basis)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  EigenDense<npe_Scalar_v> b1;
  EigenDense<npe_Scalar_v> b2;
  EigenDense<npe_Scalar_v> b3;
  igl::local_basis(v, f, b1, b2, b3);
  return std::make_tuple(npe::move(b1), npe::move(b2), npe::move(b3));

npe_end_code()


