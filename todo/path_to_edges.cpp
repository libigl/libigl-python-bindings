#include <npe.h>
#include <typedefs.h>






#include <igl/path_to_edges.h>

const char* ds_path_to_edges = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Given a path as an ordered list of N>=2 vertex indices I[0], I[1], ..., I[N-1]
   construct a list of edges [[I[0],I[1]], [I[1],I[2]], ..., [I[N-2], I[N-1]]]
   connecting each sequential pair of vertices.
  
   Inputs:
     I  #I list of vertex indices
     make_loop bool If true, include an edge connecting I[N-1] to I[0]
   Outputs:
     E  #I-1 by 2 list of edges
   
)igl_Qu8mg5v7";

npe_function(path_to_edges)
npe_doc(ds_path_to_edges)

npe_arg(i, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> e;
  bool make_loop;
  igl::path_to_edges(i, e, make_loop);
  return std::make_tuple(npe::move(e), npe::move(make_loop));

npe_end_code()
#include <igl/path_to_edges.h>

const char* ds_path_to_edges = R"igl_Qu8mg5v7(
See path_to_edges for the documentation.
)igl_Qu8mg5v7";

npe_function(path_to_edges)
npe_doc(ds_path_to_edges)

npe_arg(i, std::vector<Index> &)


npe_begin_code()

  EigenDense<npe_Scalar_> e;
  bool make_loop;
  igl::path_to_edges(i, e, make_loop);
  return std::make_tuple(npe::move(e), npe::move(make_loop));

npe_end_code()


