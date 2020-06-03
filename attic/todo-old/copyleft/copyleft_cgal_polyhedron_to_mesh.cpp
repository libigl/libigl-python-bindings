#include <npe.h>
#include <typedefs.h>






#include <igl/polyhedron_to_mesh.h>

const char* ds_polyhedron_to_mesh = R"igl_Qu8mg5v7(

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

 Convert a CGAL Polyhedron to a mesh (V,F)
      
       Templates:
         Polyhedron  CGAL Polyhedron type (e.g. Polyhedron_3)
       Inputs:
         poly  cgal polyhedron
       Outputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices
)igl_Qu8mg5v7";

npe_function(polyhedron_to_mesh)
npe_doc(ds_polyhedron_to_mesh)

npe_arg(poly, Polyhedron &)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  igl::  copyleft::  cgal::polyhedron_to_mesh(poly, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()


