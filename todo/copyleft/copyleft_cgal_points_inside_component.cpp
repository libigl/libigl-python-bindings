#include <npe.h>
#include <typedefs.h>
#include <igl/points_inside_component.h>

const char* ds_points_inside_component = R"igl_Qu8mg5v7(

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

 Determine if queries points P are inside of connected facet component
       (V, F, I), where I indicates a subset of facets that forms the
       component.
      
       Precondition:
       The input mesh must be a closed, self-intersection free,
       non-degenerated surface.  Queries points must be either inside or
       outside of the mesh (i.e. not on the surface of the mesh).
      
       Inputs:
         V  #V by 3 array of vertex positions.
         F  #F by 3 array of triangles.
         I  #I list of triangle indices to consider.
         P  #P by 3 array of query points.
      
       Outputs:
         inside  #P list of booleans that is true iff the corresponding
                 query point is inside of the mesh.
)igl_Qu8mg5v7";

npe_function(points_inside_component)
npe_doc(ds_points_inside_component)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(i, dense_float, dense_double)
npe_arg(p, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> inside;
  igl::  copyleft::  cgal::points_inside_component(v, f, i, p, inside);
  return npe::move(inside);

npe_end_code()
#include <igl/points_inside_component.h>

const char* ds_points_inside_component = R"igl_Qu8mg5v7(

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

 Determine if query points P is inside of the mesh (V, F).
       See above for precondition and I/O specs.
)igl_Qu8mg5v7";

npe_function(points_inside_component)
npe_doc(ds_points_inside_component)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(p, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> inside;
  igl::  copyleft::  cgal::points_inside_component(v, f, p, inside);
  return npe::move(inside);

npe_end_code()


