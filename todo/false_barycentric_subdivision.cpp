#include <npe.h>
#include <typedefs.h>
#include <igl/false_barycentric_subdivision.h>

const char* ds_false_barycentric_subdivision = R"igl_Qu8mg5v7(

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

 Refine the mesh by adding the barycenter of each face
   Inputs:
     V       #V by 3 coordinates of the vertices
     F       #F by 3 list of mesh faces (must be triangles)
   Outputs:
     VD      #V + #F by 3 coordinate of the vertices of the dual mesh
             The added vertices are added at the end of VD (should not be
             same references as (V,F)
     FD      #F*3 by 3 faces of the dual mesh
  
)igl_Qu8mg5v7";

npe_function(false_barycentric_subdivision)
npe_doc(ds_false_barycentric_subdivision)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> vd;
  EigenDense<npe_Scalar_> fd;
  igl::false_barycentric_subdivision(v, f, vd, fd);
  return std::make_tuple(npe::move(vd), npe::move(fd));

npe_end_code()


