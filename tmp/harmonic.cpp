#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/harmonic.h>

const char* ds_harmonic = R"igl_Qu8mg5v7(
Compute k-harmonic weight functions 'coordinates'.

Parameters
----------
v : #v by dim vertex positions
f : #f by simplex-size list of element indices
b : #b boundary indices into v
bc : #b by #w list of boundary values
k : power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
w : #v by #w array of weights

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic)
npe_doc(ds_harmonic)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(b, dense_i32, dense_i64)
npe_arg(bc, dense_f32, dense_f64)
npe_arg(k, int)
npe_begin_code()

  EigenDenseLike<npe_Matrix_v> w;
  igl::harmonic(v, f, b, bc, k, w);
  return npe::move(w);

npe_end_code()

