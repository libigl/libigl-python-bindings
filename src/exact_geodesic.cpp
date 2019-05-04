#include <npe.h>
#include <typedefs.h>
#include <igl/exact_geodesic.h>

const char* ds_exact_geodesic = R"igl_Qu8mg5v7(
Exact geodesic algorithm for the calculation of geodesics on a triangular mesh.

Parameters
----------
v : #v by 3 array of 3D vertex positions
f : #f by 3 array of mesh faces
vs : #vs by 1 array specifying indices of source vertices
fs : #fs by 1 array specifying indices of source faces
vt : #vt by 1 array specifying indices of target vertices
ft : #ft by 1 array specifying indices of target faces

Returns
-------
d : #vt+#ft by 1 array of geodesic distances of each target w.r.t. the nearest one in the source set

See also
--------


Notes
-----
Specifying a face as target/source means its center.
Implementation from https:code.google.com/archive/p/geodesic/ with the algorithm first described by Mitchell, Mount and Papadimitriou in 1987.

Examples
--------

)igl_Qu8mg5v7";

npe_function(exact_geodesic)
npe_doc(ds_exact_geodesic)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i64, dense_i64)
npe_arg(vs, npe_matches(f))
npe_arg(fs, npe_matches(f))
npe_arg(vt, npe_matches(f))
npe_arg(ft, npe_matches(f))
npe_begin_code()

  EigenDenseLike<npe_Matrix_v> d;
  igl::exact_geodesic(v, f, vs, fs, vt, ft, d);
  return npe::move(d);

npe_end_code()


