#include <npe.h>
#include <typedefs.h>






#include <igl/parallel_transport_angles.h>

const char* ds_parallel_transport_angles = R"igl_Qu8mg5v7(

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

 Inputs:
     V               #V by 3 list of mesh vertex coordinates
     F               #F by 3 list of mesh faces (must be triangles)
     FN              #F by 3 list of face normals
     E2F             #E by 2 list of the edge-to-face relation (e.g. computed
                     via igl::edge_topology)
     F2E             #F by 3 list of the face-to-edge relation (e.g. computed
                     via igl::edge_topology)
   Output:
     K               #E by 1 list of the parallel transport angles (zero
                     for all boundary edges)
  
)igl_Qu8mg5v7";

npe_function(parallel_transport_angles)
npe_doc(ds_parallel_transport_angles)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(fn, dense_float, dense_double)
npe_arg(e2_f, Eigen::MatrixXi &)
npe_arg(f2_e, Eigen::MatrixXi &)


npe_begin_code()

  EigenDense<npe_Scalar_> k;
  igl::parallel_transport_angles(v, f, fn, e2_f, f2_e, k);
  return npe::move(k);

npe_end_code()


