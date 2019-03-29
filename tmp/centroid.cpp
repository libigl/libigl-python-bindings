#include <npe.h>
#include <typedefs.h>
#include <igl/centroid.h>

const char* ds_centroid = R"igl_Qu8mg5v7(
Computes the centroid of a closed mesh using a surface integral.

Parameters
----------
v : #v by dim array of rest domain positions
f : #f by 3 array of triangle indices into v

Returns
-------
c : dim array of centroid coordinates
vol : total volume of solid

See also
--------
None

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> c, vol = centroid(v, f)
)igl_Qu8mg5v7";

npe_function(centroid)
npe_doc(ds_centroid)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  npe_Matrix_v c;
  npe_Scalar_v vol;
  igl::centroid(v, f, c, vol);
  return std::make_tuple(npe::move(c), vol);

npe_end_code()


