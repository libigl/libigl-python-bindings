#include <npe.h>
#include <typedefs.h>
#include <igl/doublearea.h>

const char* ds_doublearea = R"igl_Qu8mg5v7(

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

 DOUBLEAREA computes twice the area for each input triangle[quad]
  
   Templates:
     DerivedV  derived type of eigen matrix for V (e.g. derived from
       MatrixXd)
     DerivedF  derived type of eigen matrix for F (e.g. derived from
       MatrixXi)
     DeriveddblA  derived type of eigen matrix for dblA (e.g. derived from
       MatrixXd)
   Inputs:
     V  #V by dim list of mesh vertex positions
     F  #F by simplex_size list of mesh faces (must be triangles or quads)
   Outputs:
     dblA  #F list of triangle[quad] double areas (SIGNED only for 2D input)
  
   Known bug: For dim==3 complexity is O(#V + #F)!! Not just O(#F). This is a big deal
   if you have 1million unreferenced vertices and 1 face
)igl_Qu8mg5v7";

npe_function(doublearea)
npe_doc(ds_doublearea)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> dbl_a;
  igl::doublearea(v, f, dbl_a);
  return npe::move(dbl_a);

npe_end_code()
#include <igl/doublearea.h>

const char* ds_doublearea = R"igl_Qu8mg5v7(

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

 Stream of triangles, computes signed area...
)igl_Qu8mg5v7";

npe_function(doublearea)
npe_doc(ds_doublearea)

npe_arg(a, dense_f32, dense_f64)
npe_arg(b, dense_f32, dense_f64)
npe_arg(c, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> d;
  igl::doublearea(a, b, c, d);
  return npe::move(d);

npe_end_code()
#include <igl/doublearea_single.h>

const char* ds_doublearea_single = R"igl_Qu8mg5v7(

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

 Single triangle in 2D!
  
   This should handle streams of corners not just single corners
)igl_Qu8mg5v7";

npe_function(doublearea_single)
npe_doc(ds_doublearea_single)

npe_arg(a, dense_f32, dense_f64)
npe_arg(b, dense_f32, dense_f64)
npe_arg(c, dense_f32, dense_f64)


npe_begin_code()

  igl::doublearea_single(a, b, c);
  return ;

npe_end_code()
#include <igl/doublearea.h>

const char* ds_doublearea = R"igl_Qu8mg5v7(

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

 default behavior is to assert on NaNs and leave them in place
)igl_Qu8mg5v7";

npe_function(doublearea)
npe_doc(ds_doublearea)

npe_arg(l, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> dbl_a;
  igl::doublearea(l, dbl_a);
  return npe::move(dbl_a);

npe_end_code()
#include <igl/doublearea_quad.h>

const char* ds_doublearea_quad = R"igl_Qu8mg5v7(

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

 DOUBLEAREA_QUAD computes twice the area for each input quadrilateral
  
   Inputs:
     V  #V by dim list of mesh vertex positions
     F  #F by simplex_size list of mesh faces (must be quadrilaterals)
   Outputs:
     dblA  #F list of quadrilateral double areas
  
)igl_Qu8mg5v7";

npe_function(doublearea_quad)
npe_doc(ds_doublearea_quad)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> dbl_a;
  igl::doublearea_quad(v, f, dbl_a);
  return npe::move(dbl_a);

npe_end_code()






#include <igl/doublearea.h>

const char* ds_doublearea = R"igl_Qu8mg5v7(

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

 Same as above but use instrinsic edge lengths rather than (V,F) mesh. This
  
   Inputs:
     l  #F by dim list of edge lengths using
       for triangles, columns correspond to edges 23,31,12
     nan_replacement  what value should be used for triangles whose given
       edge lengths do not obey the triangle inequality. These may be very
       wrong (e.g., [100 1 1]) or may be nearly degenerate triangles whose
       floating point side length computation leads to breach of the triangle
       inequality. One may wish to set this parameter to 0 if side lengths l
       are _known_ to come from a valid embedding (e.g., some mesh (V,F)). In
       that case, the only circumstance the triangle inequality is broken is
       when the triangle is nearly degenerate and floating point error
       dominates: hence replacing with zero is reasonable.
   Outputs:
     dblA  #F list of triangle double areas
)igl_Qu8mg5v7";

npe_function(doublearea)
npe_doc(ds_doublearea)

npe_arg(l, dense_f32, dense_f64)
npe_arg(nan_replacement, typename Derivedl::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> dbl_a;
  igl::doublearea(l, nan_replacement, dbl_a);
  return npe::move(dbl_a);

npe_end_code()


