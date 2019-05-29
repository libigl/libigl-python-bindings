#include <npe.h>
#include <typedefs.h>






#include <igl/mesh_to_cgal_triangle_list.h>

const char* ds_mesh_to_cgal_triangle_list = R"igl_Qu8mg5v7(

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

 Convert a mesh (V,F) to a list of CGAL triangles
      
       Templates:
         Kernal  CGAL computation and construction kernel (e.g.
           CGAL::Exact_predicates_exact_constructions_kernel)
       Inputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices
       Outputs:
         T  #F list of CGAL triangles
)igl_Qu8mg5v7";

npe_function(mesh_to_cgal_triangle_list)
npe_doc(ds_mesh_to_cgal_triangle_list)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  std::vector<CGAL::Triangle_3<Kernel> > & t;
  igl::  copyleft::  cgal::mesh_to_cgal_triangle_list(v, f, t);
  return npe::move(t);

npe_end_code()


