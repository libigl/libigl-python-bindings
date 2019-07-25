// TODO: __example

#include <npe.h>
#include <typedefs.h>






#include <igl/uniformly_sample_two_manifold.h>

const char* ds_uniformly_sample_two_manifold_internal = R"igl_Qu8mg5v7(

UNIFORMLY_SAMPLE_TWO_MANIFOLD Attempt to sample a mesh uniformly by
   furthest point relaxation as described in "Fast Automatic Skinning
   Transformations"

   [Jacobson et al. 12] Section 3.3.

Parameters
----------
W  #W by dim positions of mesh in weight space
F  #F by 3 indices of triangles
k  number of samplse
push  factor by which corners should be pushed away


Returns
-------
WS  k by dim locations in weights space


See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(uniformly_sample_two_manifold_internal)
npe_doc(ds_uniformly_sample_two_manifold_internal)

npe_arg(w, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(k, int)
npe_arg(push, double)


npe_begin_code()

  // TODO: remove __copy
  Eigen::MatrixXd w_copy = w.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd ws;
  igl::uniformly_sample_two_manifold(w_copy, f_copy, k, push, ws);
  return npe::move(ws);

npe_end_code()





const char* ds_uniformly_sample_two_manifold_at_vertices = R"igl_Qu8mg5v7(

Find uniform sampling up to placing samples on mesh vertices

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

)igl_Qu8mg5v7";

npe_function(uniformly_sample_two_manifold_at_vertices)
npe_doc(ds_uniformly_sample_two_manifold_at_vertices)

npe_arg(ow, dense_float, dense_double)
npe_arg(k, int)
npe_arg(push, double)


npe_begin_code()

  // TODO: remove __copy
  Eigen::MatrixXd ow_copy = ow.template cast<double>();
  Eigen::VectorXi s;
  igl::uniformly_sample_two_manifold_at_vertices(ow_copy, k, push, s);
  return npe::move(s);

npe_end_code()


