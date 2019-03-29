#include <npe.h>
#include <typedefs.h>
#include <igl/grid.h>

const char* ds_grid = R"igl_Qu8mg5v7(

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

 Construct vertices of a regular grid, suitable for input to
   `igl::marching_cubes`
  
   Inputs:
     res  3-long list of number of vertices along the x y and z dimensions
   Outputs:
     GV  res(0)*res(1)*res(2) by 3 list of mesh vertex positions.
     
)igl_Qu8mg5v7";

npe_function(grid)
npe_doc(ds_grid)

npe_arg(res, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> gv;
  igl::grid(res, gv);
  return npe::move(gv);

npe_end_code()


