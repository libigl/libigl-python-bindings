#include <npe.h>
#include <typedefs.h>






#include <igl/mesh_to_polyhedron.h>

const char* ds_mesh_to_polyhedron = R"igl_Qu8mg5v7(

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

 Convert a mesh (V,F) to a CGAL Polyhedron
      
       Templates:
         Polyhedron  CGAL Polyhedron type (e.g. Polyhedron_3)
       Inputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices
       Outputs:
         poly  cgal polyhedron
       Returns true only if (V,F) can be converted to a valid polyhedron (i.e. if
       (V,F) is vertex and edge manifold).
)igl_Qu8mg5v7";

npe_function(mesh_to_polyhedron)
npe_doc(ds_mesh_to_polyhedron)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)


npe_begin_code()

  Polyhedron & poly;
  igl::  copyleft::  cgal::mesh_to_polyhedron(v, f, poly);
  return npe::move(poly);

npe_end_code()


