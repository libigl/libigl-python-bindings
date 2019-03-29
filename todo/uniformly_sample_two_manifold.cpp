#include <npe.h>
#include <typedefs.h>






#include <igl/uniformly_sample_two_manifold.h>

const char* ds_uniformly_sample_two_manifold = R"igl_Qu8mg5v7(

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

 UNIFORMLY_SAMPLE_TWO_MANIFOLD Attempt to sample a mesh uniformly by
   furthest point relaxation as described in "Fast Automatic Skinning
   Transformations"
  
   [Jacobson et al. 12] Section 3.3.
  
   Inputs:
     W  #W by dim positions of mesh in weight space
     F  #F by 3 indices of triangles
     k  number of samplse
     push  factor by which corners should be pushed away
   Outputs
     WS  k by dim locations in weights space
  
)igl_Qu8mg5v7";

npe_function(uniformly_sample_two_manifold)
npe_doc(ds_uniformly_sample_two_manifold)

npe_arg(w, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(k, int)
npe_arg(push, double)


npe_begin_code()

  Eigen::MatrixXd & ws;
  igl::uniformly_sample_two_manifold(w, f, k, push, ws);
  return npe::move(ws);

npe_end_code()
#include <igl/uniformly_sample_two_manifold_at_vertices.h>

const char* ds_uniformly_sample_two_manifold_at_vertices = R"igl_Qu8mg5v7(

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

 Find uniform sampling up to placing samples on mesh vertices
)igl_Qu8mg5v7";

npe_function(uniformly_sample_two_manifold_at_vertices)
npe_doc(ds_uniformly_sample_two_manifold_at_vertices)

npe_arg(ow, Eigen::MatrixXd &)
npe_arg(k, int)
npe_arg(push, double)


npe_begin_code()

  Eigen::VectorXi & s;
  igl::uniformly_sample_two_manifold_at_vertices(ow, k, push, s);
  return npe::move(s);

npe_end_code()


