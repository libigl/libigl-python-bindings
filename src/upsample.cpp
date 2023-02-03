//TODO: __example
//TODO: __miss upsample that retuns a sparse matrix and inplace
#include <common.h>
#include <npe.h>
#include <typedefs.h>

#include <igl/upsample.h>


const char* ds_upsample = R"igl_Qu8mg5v7(
  Subdivide a mesh without moving vertices: loop subdivision but odd
   vertices stay put and even vertices are just edge midpoints
Parameters
----------
     V  #V by dim  mesh vertices
     F  #F by 3  mesh triangles

Returns
-------
     NV new vertex positions, V is guaranteed to be at top
     NF new list of face indices

See also
--------


Notes
-----
- assumes (V,F) is edge-manifold.

Examples
--------

)igl_Qu8mg5v7";

npe_function(upsample)
npe_doc(ds_upsample)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_default_arg(number_of_subdivs, int, 1)


npe_begin_code()

  assert_valid_23d_tri_mesh(v, f);
  EigenDenseLike<npe_Matrix_v> nv;
  EigenDenseLike<npe_Matrix_f> nf;
  igl::upsample(v, f, nv, nf, number_of_subdivs);
  return std::make_tuple(npe::move(nv), npe::move(nf));

npe_end_code()
