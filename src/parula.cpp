#include <npe.h>
#include <typedefs.h>
#include <igl/parula.h>

const char* ds_parula = R"igl_Qu8mg5v7(
PARULA like MATLAB's parula colorpalette.

Parameters
----------
z : #z list of factors
normalize : whether to normalize Z to be tightly between [0, 1]

Returns
-------
c : #c by 3 list of rgb colors

See also
--------
jet

Notes
-----
None

Examples
--------
# Mesh in (v, f), extract z components
>>> z = v[:, 2]
>>> c = parula(z, True)
)igl_Qu8mg5v7";

npe_function(parula)
npe_doc(ds_parula)
npe_arg(z, dense_f64)
npe_arg(normalize, bool)
npe_begin_code()

  npe_Matrix_z c;
  igl::parula(z, normalize, c);
  return npe::move(c);

npe_end_code()
