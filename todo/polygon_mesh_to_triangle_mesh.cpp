#include <npe.h>
#include <typedefs.h>
#include <igl/polygon_mesh_to_triangle_mesh.h>

const char* ds_polygon_mesh_to_triangle_mesh = R"igl_Qu8mg5v7(

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

 Triangulate a general polygonal mesh into a triangle mesh.
  
   Inputs:
     vF  list of polygon index lists
   Outputs:
     F  eigen int matrix #F by 3
  
   Example:
     vector<vector<double > > vV;
     vector<vector<int > > vF;
     read_triangle_mesh("poly.obj",vV,vF);
     MatrixXd V;
     MatrixXi F;
     list_to_matrix(vV,V);
     triangulate(vF,F);
)igl_Qu8mg5v7";

npe_function(polygon_mesh_to_triangle_mesh)
npe_doc(ds_polygon_mesh_to_triangle_mesh)

npe_arg(v_f, std::vector<std::vector<int> > &)


npe_begin_code()

  EigenDense<npe_Scalar_> f;
  igl::polygon_mesh_to_triangle_mesh(v_f, f);
  return npe::move(f);

npe_end_code()
#include <igl/polygon_mesh_to_triangle_mesh.h>

const char* ds_polygon_mesh_to_triangle_mesh = R"igl_Qu8mg5v7(
See polygon_mesh_to_triangle_mesh for the documentation.
)igl_Qu8mg5v7";

npe_function(polygon_mesh_to_triangle_mesh)
npe_doc(ds_polygon_mesh_to_triangle_mesh)

npe_arg(p, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> f;
  igl::polygon_mesh_to_triangle_mesh(p, f);
  return npe::move(f);

npe_end_code()


