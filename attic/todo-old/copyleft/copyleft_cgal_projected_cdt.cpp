#include <npe.h>
#include <typedefs.h>






#include <igl/projected_cdt.h>

const char* ds_projected_cdt = R"igl_Qu8mg5v7(

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

 Given a list of objects (e.g., resulting from intersecting a triangle
       with many other triangles), construct a constrained Delaunay
       triangulation on a given plane (P), by inersting constraints for each
       object projected onto that plane.
      
       Inputs:
         objects  list of objects. This should lie on the given plane (P),
           otherwise they are added to the cdt _after_ their non-trivial
           projection
         P  plane upon which all objects lie and upon which the CDT is
           conducted
       Outputs:
         vertices  list of vertices of the CDT mesh _back on the 3D plane_
         faces  list of list of triangle indices into vertices
      
)igl_Qu8mg5v7";

npe_function(projected_cdt)
npe_doc(ds_projected_cdt)

npe_arg(objects, std::vector<CGAL::Object> &)
npe_arg(p, CGAL::Plane_3<Kernel> &)


npe_begin_code()

  std::vector<CGAL::Point_3<Kernel> > & vertices;
  std::vector<std::vector<int> > & faces;
  igl::  copyleft::  cgal::projected_cdt(objects, p, vertices, faces);
  return std::make_tuple(npe::move(vertices), npe::move(faces));

npe_end_code()
#include <igl/projected_cdt.h>

const char* ds_projected_cdt = R"igl_Qu8mg5v7(

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

 Outputs:
         V  #V by 3 list of vertices of the CDT mesh _back on the 3D plane_,
           **cast** from the number type of Kernel to the number type of
           DerivedV
         F  #F by 3 list of triangle indices into V
)igl_Qu8mg5v7";

npe_function(projected_cdt)
npe_doc(ds_projected_cdt)

npe_arg(objects, std::vector<CGAL::Object> &)
npe_arg(p, CGAL::Plane_3<Kernel> &)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  igl::  copyleft::  cgal::projected_cdt(objects, p, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()


