#include <common.h>
#include <npe.h>
#include <typedefs.h>


#include <igl/path_to_edges.h>

const char *ds_path_to_edges = R"igl_Qu8mg5v7(


Given a path as an ordered list of N>=2 vertex indices I[0], I[1], ..., I[N-1]
   construct a list of edges [[I[0],I[1]], [I[1],I[2]], ..., [I[N-2], I[N-1]]]
   connecting each sequential pair of vertices.

Parameters
----------
I  #I list of vertex indices
make_loop bool If true, include an edge connecting I[N-1] to I[0]

Returns
-------
E  #I-1 by 2 list of edges

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(path_to_edges)
npe_doc(ds_path_to_edges)

npe_arg(i, dense_int, dense_long, dense_longlong)
npe_default_arg(make_loop, bool, false)


npe_begin_code()
  EigenDense<npe_Scalar_i> i_copy = i;

  EigenDense<npe_Scalar_i> e;
  igl::path_to_edges(i_copy, e, make_loop);
  return npe::move(e);

npe_end_code()
