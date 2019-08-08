// TODO: __miss __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/triangle_triangle_adjacency.h>

const char* ds_triangle_triangle_adjacency = R"igl_Qu8mg5v7(

Constructs the triangle-triangle adjacency matrix for a given
   mesh (V,F).

Parameters
----------
F  #F by simplex_size list of mesh faces (must be triangles)

Returns
-------
TT   #F by #3 adjacent matrix, the element i,j is the id of the triangle
    adjacent to the j edge of triangle i
TTi  #F by #3 adjacent matrix, the element i,j is the id of edge of the
    triangle TT(i,j) that is adjacent with triangle i


See also
--------


Notes
-----
NOTE: the first edge of a triangle is [0,1] the second [1,2] and the third
    [2,3].  this convention is DIFFERENT from cotmatrix_entries.h

Examples
--------
  
  
)igl_Qu8mg5v7";

npe_function(triangle_triangle_adjacency)
npe_doc(ds_triangle_triangle_adjacency)

npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_tet_or_tri_mesh_faces(f);
  npe_Matrix_f tt;
  npe_Matrix_f t_ti;
  igl::triangle_triangle_adjacency(f, tt, t_ti);
  return std::make_tuple(npe::move(tt), npe::move(t_ti));

npe_end_code()


