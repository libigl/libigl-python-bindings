#include <npe.h>
#include <typedefs.h>
#include <igl/flood_fill.h>

const char* ds_flood_fill = R"igl_Qu8mg5v7(

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

 Given a 3D array with sparse non-nan (number?) data fill in the NaNs via
   flood fill. This should ensure that, e.g., if data near 0 always has a band
   (surface) of numbered and signed data, then components of nans will be
   correctly signed.
  
   Inputs:
     res  3-long list of dimensions of grid
     S  res(0)*res(1)*res(2)  list of scalar values (with (many) nans), see
       output
   Outputs:
     S  flood fill data in place
)igl_Qu8mg5v7";

npe_function(flood_fill)
npe_doc(ds_flood_fill)

npe_arg(res, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  igl::flood_fill(res, s);
  return npe::move(s);

npe_end_code()


