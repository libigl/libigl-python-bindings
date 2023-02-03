#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/comb_line_field.h>

const char *ds_comb_line_field = R"igl_Qu8mg5v7(

Parameters
----------
V          #V by 3 eigen Matrix of mesh vertex 3D positions
F          #F by 3 eigen Matrix of face indices
PD1in      #F by 3 eigen Matrix of the first per face cross field vector

Returns
-------
PD1out      #F by 3 eigen Matrix of the first combed cross field vector

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(comb_line_field)
npe_doc(ds_comb_line_field)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(pd1in, npe_matches(v))


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_rows_match(f, pd1in, "F", "PD1in");
  assert_cols_equals(pd1in, 3, "PD1in");

  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;
  EigenDenseLike<npe_Matrix_v> pd1in_copy = pd1in;

  EigenDenseLike<npe_Matrix_v> pd1out;
  igl::comb_line_field(v_copy, f_copy, pd1in_copy, pd1out);
  return npe::move(pd1out);

npe_end_code()


