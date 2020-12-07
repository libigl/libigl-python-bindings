#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/marching_cubes.h>

const char* ds_marching_cubes = R"igl_Qu8mg5v7(

marching_cubes performs marching cubes reconstruction on a grid defined by values, and 
points, and generates a mesh defined by vertices and faces

Parameters
----------
S   nx*ny*nz list of values at each grid corner i.e. S(x + y*xres + z*xres*yres) for corner (x,y,z)
GV  nx*ny*nz by 3 array of corresponding grid corner vertex locations
nx  resolutions of the grid in x dimension
ny  resolutions of the grid in y dimension
nz  resolutions of the grid in z dimension
isovalue  the isovalue of the surface to reconstruct


Returns
-------
V  #V by 3 list of mesh vertex positions
F  #F by 3 list of mesh triangle indices into rows of V

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(marching_cubes)
npe_doc(ds_marching_cubes)
npe_arg(s, dense_float, dense_double)
npe_arg(gv, dense_float, dense_double)
npe_arg(nx, int)
npe_arg(ny, int)
npe_arg(nz, int)
npe_default_arg(isovalue, float, 0.0f)

npe_begin_code()
    
    EigenDenseLike<npe_Matrix_v> nv;
    EigenDenseLike<npe_Matric_f> nf;

    igl::marching_cubes(s, gv, nx, ny, nz, isovalue, nv, nf);

    return std::make_tuple(npe::move(nv), npe::move(nf));
npe_end_code()