#include <npe.h>
#include <typedefs.h>
#include <igl/jet.h>

const char* ds_jet = R"igl_Qu8mg5v7(
JET like MATLAB's jet colorpalette.

Parameters
----------
z : #z list of factors
normalize : whether to normalize Z to be tightly between [0, 1]

Returns
-------
c : #c by 3 list of rgb colors

See also
--------
parula

Notes
-----
None

Examples
--------
# Mesh in (v, f), extract z components
>>> z = v[:, 2]
>>> c = jet(z, True)
)igl_Qu8mg5v7";

npe_function(jet)
npe_doc(ds_jet)
npe_arg(z, dense_f32, dense_f64)
npe_arg(normalize, bool)
npe_begin_code()

  npe_Matrix_z c;
  igl::jet(z, normalize, c);
  return npe::move(c);

npe_end_code()

