#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/triangle/triangulate.h>

const char* ds_triangulate = R"igl_Qu8mg5v7(
Triangulate the interior of a polygon using the triangle library.

Parameters
----------
v : #v by 2 array of 2D vertex positions
e : #e by 2 array of vertex ids forming unoriented edges of the boundary of the polygon
h : #h by 2 coordinates of points contained inside holes of the polygon
m : optional #v list of markers for input vertices
flags : string of options pass to triangle (see triangle documentation) (default 'a0.005q')

Returns
-------
v2 : #v2 by 2 coordinates of the vertives of the generated triangulation
f2 : #f2 by 3 array of indices forming the faces of the generated triangulation
m2 : (only if you passed in m) #v2 list of markers for output vertices

See also
--------

Notes
-----

Examples
--------
>>> v2, f2 = triangulate(v, e, h)
)igl_Qu8mg5v7";

npe_function(triangulate)
npe_doc(ds_triangulate)
npe_arg(v, dense_float, dense_double)
npe_arg(e, dense_int, dense_long, dense_longlong)
npe_arg(h, dense_float, dense_double) // TODO: npe_matches bug
// TODO: Optionally support extra parameters
npe_default_arg(flags, std::string, "a0.005qQ")
npe_begin_code()
  assert_cols_equals(v, 2, "v");
  assert_nonzero_rows(v, "v");
  assert_cols_equals(e, 2, "e");
  assert_nonzero_rows(e, "e");
  if (h.rows() != 0 && h.cols() != 0) {
      assert_cols_equals(h, 2, "h");
  }
  EigenDenseLike<npe_Matrix_v> v2;
  EigenDenseLike<npe_Matrix_e> f2;

  igl::triangle::triangulate(v, e, h, flags, v2, f2);
  return std::make_tuple(npe::move(v2), npe::move(f2));

npe_end_code()

