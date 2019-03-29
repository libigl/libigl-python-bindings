#include <tuple>
#include <npe.h>
#include <igl/principal_curvature.h>

const char* ds_principal_curvature = R"igl_Qu8mg5v7(
Compute the principal curvature directions and magnitude of the given triangle mesh.

Parameters
----------
v : vertex array of size #V by 3
f : face index array #F by 3 list of mesh faces (must be triangles)
radius : controls the size of the neighbourhood used, 1 = average edge length (default: 5)
use_k_ring : (default: True)

Returns
-------
pd1 : #v by 3 maximal curvature direction for each vertex
pd2 : #v by 3 minimal curvature direction for each vertex
pv1 : #v by 1 maximal curvature value for each vertex
pv2 : #v by 1 minimal curvature value for each vertex

See also
--------
average_onto_faces, average_onto_vertices

Notes
-----
This function has been developed by: Nikolas De Giorgis, Luigi Rocca and Enrico Puppo.
The algorithm is based on: Efficient Multi-scale Curvature and Crease Estimation
Daniele Panozzo, Enrico Puppo, Luigi Rocca GraVisMa, 2010

Examples
--------
# Mesh in (v, f)
>>> pd1, pd2, pv1, pv2 = principal_curvature(v, f)
)igl_Qu8mg5v7";

npe_function(principal_curvature)
npe_doc(ds_principal_curvature)
npe_arg(v, dense_f64, dense_f32)
npe_arg(f, dense_i32, dense_i64)
npe_default_arg(radius, int, 5)
npe_default_arg(use_k_ring, bool, true)
npe_begin_code()

  npe_Matrix_v pd1;
  npe_Matrix_v pd2;
  npe_Matrix_v pv1;
  npe_Matrix_v pv2;

  igl::principal_curvature(v, f, pd1, pd2, pv1, pv2, radius, use_k_ring);
  return std::make_tuple(npe::move(pd1), npe::move(pd2), npe::move(pv1), npe::move(pv2));

npe_end_code()


