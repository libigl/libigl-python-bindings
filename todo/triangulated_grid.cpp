#include <npe.h>
#include <typedefs.h>






#include <igl/triangulated_grid.h>

const char* ds_triangulated_grid = R"igl_Qu8mg5v7(

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

 Create a regular grid of elements (only 2D supported, currently)
   Vertex position order is compatible with `igl::grid`
  
   Inputs:
     nx  number of vertices in the x direction
     ny  number of vertices in the y direction
   Outputs:
     GV  nx*ny by 2 list of mesh vertex positions.
     GF  2*(nx-1)*(ny-1) by 3  list of triangle indices
  
     See also: grid, quad_grid
)igl_Qu8mg5v7";

npe_function(triangulated_grid)
npe_doc(ds_triangulated_grid)

npe_arg(nx, XType &)
npe_arg(ny, YType &)


npe_begin_code()

  EigenDense<npe_Scalar_> gv;
  EigenDense<npe_Scalar_> gf;
  igl::triangulated_grid(nx, ny, gv, gf);
  return std::make_tuple(npe::move(gv), npe::move(gf));

npe_end_code()
#include <igl/triangulated_grid.h>

const char* ds_triangulated_grid = R"igl_Qu8mg5v7(
See triangulated_grid for the documentation.
)igl_Qu8mg5v7";

npe_function(triangulated_grid)
npe_doc(ds_triangulated_grid)

npe_arg(nx, XType &)
npe_arg(ny, YType &)


npe_begin_code()

  EigenDense<npe_Scalar_> gf;
  igl::triangulated_grid(nx, ny, gf);
  return npe::move(gf);

npe_end_code()


