#include <npe.h>
#include <typedefs.h>
#include <igl/normal_derivative.h>

const char* ds_normal_derivative = R"igl_Qu8mg5v7(

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

 NORMAL_DERIVATIVE Computes the directional derivative **normal** to
   **all** (half-)edges of a triangle mesh (not just boundary edges). These
   are integrated along the edge: they're the per-face constant gradient dot
   the rotated edge vector (unit rotated edge vector for direction then
   magnitude for integration).
  
   Inputs:
     V  #V by dim list of mesh vertex positions
     F  #F by 3|4 list of triangle|tetrahedron indices into V
   Outputs:
     DD  #F*3|4 by #V sparse matrix representing operator to compute
       directional derivative with respect to each facet of each element.
  
)igl_Qu8mg5v7";

npe_function(normal_derivative)
npe_doc(ds_normal_derivative)

npe_arg(v, dense_f32, dense_f64)
npe_arg(ele, dense_f32, dense_f64)


npe_begin_code()

  Sparse_f64 dd;
  igl::normal_derivative(v, ele, dd);
  return npe::move(dd);

npe_end_code()


