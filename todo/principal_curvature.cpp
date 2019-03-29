#include <npe.h>
#include <typedefs.h>






#include <igl/principal_curvature.h>

const char* ds_principal_curvature = R"igl_Qu8mg5v7(

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

 Compute the principal curvature directions and magnitude of the given triangle mesh
     DerivedV derived from vertex positions matrix type: i.e. MatrixXd
     DerivedF derived from face indices matrix type: i.e. MatrixXi
   Inputs:
     V       eigen matrix #V by 3
     F       #F by 3 list of mesh faces (must be triangles)
     radius  controls the size of the neighbourhood used, 1 = average edge length
  
   Outputs:
     PD1 #V by 3 maximal curvature direction for each vertex.
     PD2 #V by 3 minimal curvature direction for each vertex.
     PV1 #V by 1 maximal curvature value for each vertex.
     PV2 #V by 1 minimal curvature value for each vertex.
  
   See also: average_onto_faces, average_onto_vertices
  
   This function has been developed by: Nikolas De Giorgis, Luigi Rocca and Enrico Puppo.
   The algorithm is based on:
   Efficient Multi-scale Curvature and Crease Estimation
   Daniele Panozzo, Enrico Puppo, Luigi Rocca
   GraVisMa, 2010
)igl_Qu8mg5v7";

npe_function(principal_curvature)
npe_doc(ds_principal_curvature)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> pd1;
  EigenDense<npe_Scalar_> pd2;
  EigenDense<npe_Scalar_> pv1;
  EigenDense<npe_Scalar_> pv2;
  unsigned int radius;
  bool use_kring;
  igl::principal_curvature(v, f, pd1, pd2, pv1, pv2, radius, use_kring);
  return std::make_tuple(npe::move(pd1), npe::move(pd2), npe::move(pv1), npe::move(pv2), npe::move(radius), npe::move(use_kring));

npe_end_code()


