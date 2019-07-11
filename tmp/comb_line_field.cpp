// TODO: Maybe need more templates. deduced conflict types __bug

#include <npe.h>
#include <typedefs.h>
#include <igl/comb_line_field.h>

const char* ds_comb_line_field = R"igl_Qu8mg5v7(

Parameters
----------
V          #V by 3 eigen Matrix of mesh vertex 3D positions
F          #F by 4 eigen Matrix of face (quad) indices
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

npe_function(comb_line_field)
npe_doc(ds_comb_line_field)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(pd1in, npe_matches(v))


npe_begin_code()

  npe_Matrix_v pd1out;
  igl::comb_line_field(v, f, pd1in, pd1out);
  return npe::move(pd1out);

npe_end_code()


