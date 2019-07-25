//TODO: __miss
//TODO: __example
// missing slice_tets file
#include <npe.h>
#include <typedefs.h>
#include <igl/slice_tets.h>


const char* ds_slice_tets = R"igl_Qu8mg5v7(
 SLICE_TETS Slice through a tet mesh (V,T) along a given plane (via its
   implicit equation).
Parameters
----------
     V  #V by 3 list of tet mesh vertices
     T  #T by 4 list of tet indices into V
     plane  list of 4 coefficients in the plane equation: [x y z 1]'*plane = 0
     S  #V list of values so that S = 0 is the desired isosurface

Returns
-------
     SV  #SV by 3 list of triangle mesh vertices along slice
     SF  #SF by 3 list of triangles indices into SV
     J  #SF list of indices into T revealing from which tet each faces comes
     BC  #SU by #V list of barycentric coordinates (or more generally: linear
       interpolation coordinates) so that SV = BC*V

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(slice_tets)
npe_doc(ds_slice_tets)

npe_arg(v, dense_float, dense_double)
npe_arg(t, dense_int, dense_long)
npe_arg(s, dense_float, dense_double)


npe_begin_code()

  npe_Matrix_v sv;
  npe_Matrix_t sf;
  npe_Matrix_t j;
  Eigen::SparseMatrix<npe_Scalar_v> & bc;
  igl::slice_tets(v, t, s, sv, sf, j, bc);
  return std::make_tuple(npe::move(sv), npe::move(sf), npe::move(j), npe::move(bc));

npe_end_code()


