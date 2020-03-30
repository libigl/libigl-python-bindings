#include <npe.h>
#include <typedefs.h>
#include <pybind11/stl.h>
#include <igl/polygon_mesh_to_triangle_mesh.h>

const char *ds_polygon_mesh_to_triangle_mesh = R"igl_Qu8mg5v7(
 Triangulate a general polygonal mesh into a triangle mesh.

Parameters
----------
vF  list of polygon index lists

Returns
-------
F  eigen int matrix #F by 3

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(polygon_mesh_to_triangle_mesh_from_list)
npe_doc(ds_polygon_mesh_to_triangle_mesh)

npe_arg(v_f, std::vector< std::vector<int> >)


npe_begin_code()

  EigenDenseInt f;
  igl::polygon_mesh_to_triangle_mesh(v_f, f);
  return npe::move(f);

npe_end_code()



const char *ds_polygon_mesh_to_triangle_mesh1 = R"igl_Qu8mg5v71(
 Triangulate a general polygonal mesh into a triangle mesh.

Parameters
----------
vF  matrix polygon index lists

Returns
-------
F  eigen int matrix #F by 3

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v71";

npe_function(polygon_mesh_to_triangle_mesh)
npe_doc(ds_polygon_mesh_to_triangle_mesh1)

npe_arg(p, dense_int, dense_long, dense_longlong)


npe_begin_code()
  std::vector<std::vector<npe_Scalar_p> > vP;
  igl::matrix_to_list(p,vP);

  EigenDense<npe_Scalar_p> f;
  igl::polygon_mesh_to_triangle_mesh(vP, f);
  return npe::move(f);

npe_end_code()


