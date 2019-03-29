#include <npe.h>
#include <typedefs.h>
#include <igl/connect_boundary_to_infinity.h>

const char* ds_connect_boundary_to_infinity = R"igl_Qu8mg5v7(

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

 Connect all boundary edges to a fictitious point at infinity.
  
   Inputs:
     F  #F by 3 list of face indices into some V
   Outputs:
     FO  #F+#O by 3 list of face indices into [V;inf inf inf], original F are
       guaranteed to come first. If (V,F) was a manifold mesh, now it is
       closed with a possibly non-manifold vertex at infinity (but it will be
       edge-manifold).
)igl_Qu8mg5v7";

npe_function(connect_boundary_to_infinity)
npe_doc(ds_connect_boundary_to_infinity)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> fo;
  igl::connect_boundary_to_infinity(f, fo);
  return npe::move(fo);

npe_end_code()
#include <igl/connect_boundary_to_infinity.h>

const char* ds_connect_boundary_to_infinity = R"igl_Qu8mg5v7(

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

 Inputs:
     V  #V by 3 list of vertex positions
     F  #F by 3 list of face indices into some V
   Outputs:
     VO  #V+1 by 3 list of vertex positions, original V are guaranteed to
       come first. Last point is inf, inf, inf
     FO  #F+#O by 3 list of face indices into VO
   
)igl_Qu8mg5v7";

npe_function(connect_boundary_to_infinity)
npe_doc(ds_connect_boundary_to_infinity)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> vo;
  EigenDense<npe_Scalar_> fo;
  igl::connect_boundary_to_infinity(v, f, vo, fo);
  return std::make_tuple(npe::move(vo), npe::move(fo));

npe_end_code()






#include <igl/connect_boundary_to_infinity.h>

const char* ds_connect_boundary_to_infinity = R"igl_Qu8mg5v7(

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

 Inputs:
     inf_index  index of point at infinity (usually V.rows() or F.maxCoeff())
)igl_Qu8mg5v7";

npe_function(connect_boundary_to_infinity)
npe_doc(ds_connect_boundary_to_infinity)

npe_arg(f, dense_i32, dense_i64)
npe_arg(inf_index, typename DerivedF::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> fo;
  igl::connect_boundary_to_infinity(f, inf_index, fo);
  return npe::move(fo);

npe_end_code()


