#include <npe.h>
#include <typedefs.h>
#include <igl/marching_cubes.h>

const char* ds_marching_cubes = R"igl_Qu8mg5v7(

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

 marching_cubes( values, points, x_res, y_res, z_res, vertices, faces )
    
     performs marching cubes reconstruction on the grid defined by values, and
     points, and generates vertices and faces
    
     Input:
      values  #number_of_grid_points x 1 array -- the scalar values of an
        implicit function defined on the grid points (<0 in the inside of the
        surface, 0 on the border, >0 outside)
      points  #number_of_grid_points x 3 array -- 3-D positions of the grid
        points, ordered in x,y,z order:
          points[index] = the point at (x,y,z) where :
          x = (index % (xres -1),
          y = (index / (xres-1)) %(yres-1),
          z = index / (xres -1) / (yres -1) ).
          where x,y,z index x, y, z dimensions
          i.e. index = x + y*xres + z*xres*yres
      xres  resolutions of the grid in x dimension
      yres  resolutions of the grid in y dimension
      zres  resolutions of the grid in z dimension
     Output:
       vertices  #V by 3 list of mesh vertex positions
       faces  #F by 3 list of mesh triangle indices
    
)igl_Qu8mg5v7";

npe_function(marching_cubes)
npe_doc(ds_marching_cubes)

npe_arg(values, dense_float, dense_double)
npe_arg(points, dense_float, dense_double)
npe_arg(x_res, unsigned int)
npe_arg(y_res, unsigned int)
npe_arg(z_res, unsigned int)


npe_begin_code()

  EigenDense<npe_Scalar_> vertices;
  EigenDense<npe_Scalar_> faces;
  igl::  copyleft::marching_cubes(values, points, x_res, y_res, z_res, vertices, faces);
  return std::make_tuple(npe::move(vertices), npe::move(faces));

npe_end_code()


