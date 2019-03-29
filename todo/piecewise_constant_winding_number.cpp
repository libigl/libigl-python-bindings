#include <npe.h>
#include <typedefs.h>
#include <igl/piecewise_constant_winding_number.h>

const char* ds_piecewise_constant_winding_number = R"igl_Qu8mg5v7(
See piecewise_constant_winding_number for the documentation.
)igl_Qu8mg5v7";

npe_function(piecewise_constant_winding_number)
npe_doc(ds_piecewise_constant_winding_number)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  igl::piecewise_constant_winding_number(f);
  return ;

npe_end_code()






#include <igl/piecewise_constant_winding_number.h>

const char* ds_piecewise_constant_winding_number = R"igl_Qu8mg5v7(

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

 PIECEWISE_CONSTANT_WINDING_NUMBER Determine if a given mesh induces a
   piecewise constant winding number field: Is this mesh valid input to solid
   set operations.  **Assumes** that `(V,F)` contains no self-intersections
   (including degeneracies and co-incidences).  If there are co-planar and
   co-incident vertex placements, a mesh could _fail_ this combinatorial test
   but still induce a piecewise-constant winding number _geometrically_. For
   example, consider a hemisphere with boundary and then pinch the boundary
   "shut" along a line segment. The **_bullet-proof_** check is to first
   resolve all self-intersections in `(V,F) -> (SV,SF)` (i.e. what the
   `igl::copyleft::cgal::piecewise_constant_winding_number` overload does).
  
   Inputs:
     F  #F by 3 list of triangle indices into some (abstract) list of
       vertices V
     uE  #uE by 2 list of unique edges indices into V
     uE2E  #uE list of lists of indices into directed edges (#F * 3)
   Returns true if the mesh _combinatorially_ induces a piecewise constant
   winding number field.
  
)igl_Qu8mg5v7";

npe_function(piecewise_constant_winding_number)
npe_doc(ds_piecewise_constant_winding_number)

npe_arg(f, dense_i32, dense_i64)
npe_arg(u_e, dense_f32, dense_f64)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)


npe_begin_code()

  igl::piecewise_constant_winding_number(f, u_e, u_e2_e);
  return ;

npe_end_code()


