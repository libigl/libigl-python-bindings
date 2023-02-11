#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/comb_cross_field.h>

const char* ds_comb_cross_field = R"igl_Qu8mg5v7(

Parameters
----------
     V          #V by 3 eigen Matrix of mesh vertex 3D positions
     F          #F by 3 eigen Matrix of face indices
     PD1in      #F by 3 eigen Matrix of the first per face cross field vector
     PD2in      #F by 3 eigen Matrix of the second per face cross field vector

Returns
-------
     PD1out      #F by 3 eigen Matrix of the first combed cross field vector
     PD2out      #F by 3 eigen Matrix of the second combed cross field vector

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(comb_cross_field)
npe_doc(ds_comb_cross_field)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(pd1in, npe_matches(v))
npe_arg(pd2in, npe_matches(v))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_rows_match(f, pd1in, "F", "PD1in");
  assert_rows_match(f, pd2in, "F", "PD2in");
  assert_cols_equals(pd1in, 3, "PD1in");
  assert_cols_equals(pd2in, 3, "PD2in");

  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;
  EigenDenseLike<npe_Matrix_v> pd1in_copy = pd1in;
  EigenDenseLike<npe_Matrix_v> pd2in_copy = pd2in;

  EigenDenseLike<npe_Matrix_v> pd1out;
  EigenDenseLike <npe_Matrix_v> pd2out;
  igl::comb_cross_field(v_copy, f_copy, pd1in_copy, pd2in_copy, pd1out, pd2out);
  return std::make_tuple(npe::move(pd1out), npe::move(pd2out));

npe_end_code()


