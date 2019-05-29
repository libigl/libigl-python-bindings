#include <npe.h>
#include <typedefs.h>
#include <igl/component_inside_component.h>

const char* ds_component_inside_component = R"igl_Qu8mg5v7(

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

 Determine if connected facet component (V1, F1, I1) is inside of
         connected facet component (V2, F2, I2).
        
         Precondition:
         Both components must represent closed, self-intersection free,
         non-degenerated surfaces that are the boundary of 3D volumes. In
         addition, (V1, F1, I1) must not intersect with (V2, F2, I2).
        
         Inputs:
           V1  #V1 by 3 list of vertex position of mesh 1
           F1  #F1 by 3 list of triangles indices into V1
           I1  #I1 list of indices into F1, indicate the facets of component
           V2  #V2 by 3 list of vertex position of mesh 2
           F2  #F2 by 3 list of triangles indices into V2
           I2  #I2 list of indices into F2, indicate the facets of component
        
         Outputs:
           return true iff (V1, F1, I1) is entirely inside of (V2, F2, I2).
)igl_Qu8mg5v7";

npe_function(component_inside_component)
npe_doc(ds_component_inside_component)

npe_arg(v1, dense_float, dense_double)
npe_arg(f1, dense_float, dense_double)
npe_arg(i1, dense_float, dense_double)
npe_arg(v2, dense_float, dense_double)
npe_arg(f2, dense_float, dense_double)
npe_arg(i2, dense_float, dense_double)


npe_begin_code()

  igl::  copyleft::  cgal::component_inside_component(v1, f1, i1, v2, f2, i2);
  return ;

npe_end_code()
#include <igl/component_inside_component.h>

const char* ds_component_inside_component = R"igl_Qu8mg5v7(

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

 Determine if mesh (V1, F1) is inside of mesh (V2, F2).
        
         Precondition:
         Both meshes must be closed, self-intersection free, non-degenerated
         surfaces that are the boundary of 3D volumes.  They should not
         intersect each other.
        
         Inputs:
           V1  #V1 by 3 list of vertex position of mesh 1
           F1  #F1 by 3 list of triangles indices into V1
           V2  #V2 by 3 list of vertex position of mesh 2
           F2  #F2 by 3 list of triangles indices into V2
        
         Outputs:
           return true iff (V1, F1) is entirely inside of (V2, F2).
)igl_Qu8mg5v7";

npe_function(component_inside_component)
npe_doc(ds_component_inside_component)

npe_arg(v1, dense_float, dense_double)
npe_arg(f1, dense_float, dense_double)
npe_arg(v2, dense_float, dense_double)
npe_arg(f2, dense_float, dense_double)


npe_begin_code()

  igl::  copyleft::  cgal::component_inside_component(v1, f1, v2, f2);
  return ;

npe_end_code()


