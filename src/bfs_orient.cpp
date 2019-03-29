#include <npe.h>
#include <typedefs.h>
#include <igl/bfs_orient.h>

const char* ds_bfs_orient = R"igl_Qu8mg5v7(
Consistently orient faces in orientable patches using BFS.

Parameters
----------
f : #F by 3 list of faces

Returns
-------
A tuple, (ff, c) where:
 * ff is a #F by 3 list of faces which are consistently oriented with
 * c is a #F array of connected component ids

See also
--------

Notes
-----

Examples
--------
>>> v, f, _ = igl.readOFF("test.off)
>>> ff, c = igl.bfs_orient(f)

)igl_Qu8mg5v7";

npe_function(bfs_orient)
npe_doc(ds_bfs_orient)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  npe_Matrix_f ff, c;
  igl::bfs_orient(f, ff, c);
  return std::make_tuple(npe::move(ff), npe::move(c));

npe_end_code()
