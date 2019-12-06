#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/false_barycentric_subdivision.h>

const char *ds_false_barycentric_subdivision = R"igl_Qu8mg5v7(

 Refine the mesh by adding the barycenter of each face

Parameters
----------
  V       #V by 3 coordinates of the vertices
  F       #F by 3 list of mesh faces (must be triangles)

Returns
-------
  VD      #V + #F by 3 coordinate of the vertices of the dual mesh
             The added vertices are added at the end of VD (should not be
             same references as (V,F)
  FD      #F*3 by 3 faces of the dual mesh

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(false_barycentric_subdivision)
npe_doc(ds_false_barycentric_subdivision)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  EigenDenseLike<npe_Scalar_v> vd;
  EigenDenseLike<npe_Scalar_f> fd;
  igl::false_barycentric_subdivision(v, f, vd, fd);
  return std::make_tuple(npe::move(vd), npe::move(fd));

npe_end_code()


