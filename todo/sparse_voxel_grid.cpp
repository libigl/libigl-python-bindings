#include <npe.h>
#include <typedefs.h>






#include <igl/sparse_voxel_grid.h>

const char* ds_sparse_voxel_grid = R"igl_Qu8mg5v7(

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

 sparse_voxel_grid( p0, scalarFunc, eps, CV, CS, CI )
  
   Given a point, p0, on an isosurface, construct a shell of epsilon sized cubes surrounding the surface.
   These cubes can be used as the input to marching cubes.
  
   Input:
    p0  A 3D point on the isosurface surface defined by scalarFunc(x) = 0
    scalarFunc  A scalar function from R^3 to R -- points which map to 0 lie
                on the surface, points which are negative lie inside the surface,
                and points which are positive lie outside the surface
    eps  The edge length of the cubes surrounding the surface
    expected_number_of_cubes  This pre-allocates internal data structures to speed things up
   Output:
     CS  #cube-vertices by 1 list of scalar values at the cube vertices
     CV  #cube-vertices by 3 list of cube vertex positions
     CI  #number of cubes by 8 list of indexes into CS and CV. Each row represents a cube
  
)igl_Qu8mg5v7";

npe_function(sparse_voxel_grid)
npe_doc(ds_sparse_voxel_grid)

npe_arg(p0, dense_f32, dense_f64)
npe_arg(scalar_func, Func &)
npe_arg(eps, double)
npe_arg(expected_number_of_cubes, int)


npe_begin_code()

  EigenDense<npe_Scalar_> cs;
  EigenDense<npe_Scalar_> cv;
  EigenDense<npe_Scalar_> ci;
  igl::sparse_voxel_grid(p0, scalar_func, eps, expected_number_of_cubes, cs, cv, ci);
  return std::make_tuple(npe::move(cs), npe::move(cv), npe::move(ci));

npe_end_code()


