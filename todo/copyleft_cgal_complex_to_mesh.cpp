#include <npe.h>
#include <typedefs.h>






#include <igl/complex_to_mesh.h>

const char* ds_complex_to_mesh = R"igl_Qu8mg5v7(

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

 Templates:
         Tr  CGAL triangulation type, e.g.
           CGAL::Surface_mesh_default_triangulation_3
       Inputs
         c2t3  2-complex (surface) living in a 3d triangulation (e.g. result of
           CGAL::make_surface_mesh)
       Outputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices
       Returns true iff conversion was successful, failure can ok if CGAL code
       can't figure out ordering.
      
)igl_Qu8mg5v7";

npe_function(complex_to_mesh)
npe_doc(ds_complex_to_mesh)

npe_arg(c2t3, CGAL::Complex_2_in_triangulation_3<Tr> &)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  igl::  copyleft::  cgal::complex_to_mesh(c2t3, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()


