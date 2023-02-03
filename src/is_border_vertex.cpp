#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/is_border_vertex.h>
#include <pybind11/stl.h>

const char *ds_is_border_vertex = R"igl_Qu8mg5v7(
Determine vertices on open boundary of a (manifold) mesh with triangle faces F
Parameters
----------
  V  #V by dim list of vertex positions
  F  #F by 3 list of triangle indices

Returns
-------
#V vector of bools revealing whether vertices are on boundary

See also
--------


Notes
-----
Known Bugs:
   - assumes mesh is edge manifold

Examples
--------



)igl_Qu8mg5v7";

npe_function(is_border_vertex)
npe_doc(ds_is_border_vertex)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_valid_23d_tri_mesh(v, f);
  const auto res = igl::is_border_vertex(f);
  return res;

npe_end_code()


