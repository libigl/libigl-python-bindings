#include <npe.h>
#include <typedefs.h>
#include <igl/slice_tets.h>

const char* ds_slice_tets = R"igl_Qu8mg5v7(
See slice_tets for the documentation.
)igl_Qu8mg5v7";

npe_function(slice_tets)
npe_doc(ds_slice_tets)

npe_arg(v, dense_f32, dense_f64)
npe_arg(t, dense_f32, dense_f64)
npe_arg(s, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> sv;
  EigenDense<npe_Scalar_> sf;
  EigenDense<npe_Scalar_> j;
  igl::slice_tets(v, t, s, sv, sf, j);
  return std::make_tuple(npe::move(sv), npe::move(sf), npe::move(j));

npe_end_code()
#include <igl/slice_tets.h>

const char* ds_slice_tets = R"igl_Qu8mg5v7(

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
     sE  #SV by 2 list of sorted edge indices into V
     lambda  #SV by 1 list of parameters along each edge in sE so that:
       SV(i,:) = V(sE(i,1),:)*lambda(i) + V(sE(i,2),:)*(1-lambda(i));
)igl_Qu8mg5v7";

npe_function(slice_tets)
npe_doc(ds_slice_tets)

npe_arg(v, dense_f32, dense_f64)
npe_arg(t, dense_f32, dense_f64)
npe_arg(s, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> sv;
  EigenDense<npe_Scalar_> sf;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> s_e;
  EigenDense<npe_Scalar_> lambda;
  igl::slice_tets(v, t, s, sv, sf, j, s_e, lambda);
  return std::make_tuple(npe::move(sv), npe::move(sf), npe::move(j), npe::move(s_e), npe::move(lambda));

npe_end_code()






#include <igl/slice_tets.h>

const char* ds_slice_tets = R"igl_Qu8mg5v7(

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

 SLICE_TETS Slice through a tet mesh (V,T) along a given plane (via its
   implicit equation).
  
   Inputs:
     V  #V by 3 list of tet mesh vertices
     T  #T by 4 list of tet indices into V 
     plane  list of 4 coefficients in the plane equation: [x y z 1]'*plane = 0
     S  #V list of values so that S = 0 is the desired isosurface
   Outputs:
     SV  #SV by 3 list of triangle mesh vertices along slice
     SF  #SF by 3 list of triangles indices into SV
     J  #SF list of indices into T revealing from which tet each faces comes
     BC  #SU by #V list of barycentric coordinates (or more generally: linear
       interpolation coordinates) so that SV = BC*V
   
)igl_Qu8mg5v7";

npe_function(slice_tets)
npe_doc(ds_slice_tets)

npe_arg(v, dense_f32, dense_f64)
npe_arg(t, dense_f32, dense_f64)
npe_arg(s, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> sv;
  EigenDense<npe_Scalar_> sf;
  EigenDense<npe_Scalar_> j;
  Eigen::SparseMatrix<BCType> & bc;
  igl::slice_tets(v, t, s, sv, sf, j, bc);
  return std::make_tuple(npe::move(sv), npe::move(sf), npe::move(j), npe::move(bc));

npe_end_code()


