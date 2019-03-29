#include <npe.h>
#include <typedefs.h>






#include <igl/sample_edges.h>

const char* ds_sample_edges = R"igl_Qu8mg5v7(

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

 Compute samples_per_edge extra points along each edge in E defined over
   vertices of V.
  
   Inputs:
     V  vertices over which edges are defined, # vertices by dim
     E  edge list, # edges by 2
     k  number of extra samples to be computed along edge not
          including start and end points
   Output:
     S  sampled vertices, size less than # edges * (2+k) by dim always begins
          with V so that E is also defined over S
)igl_Qu8mg5v7";

npe_function(sample_edges)
npe_doc(ds_sample_edges)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(e, Eigen::MatrixXi &)
npe_arg(k, int)


npe_begin_code()

  Eigen::MatrixXd & s;
  igl::sample_edges(v, e, k, s);
  return npe::move(s);

npe_end_code()


