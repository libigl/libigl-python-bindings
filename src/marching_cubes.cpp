// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Thomas
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
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
        points, ordered in x,y,z order:
        points[index] = the point at (x,y,z) where :
            x = (index % (xres -1),
            y = (index / (xres-1)) %(yres-1),
            z = index / (xres -1) / (yres -1) ).
            where x,y,z index x, y, z dimensions
            i.e. index = x + y*xres + z*xres*yres
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
>> import numpy as np
>> K = np.linspace( -1.0, 1.0, 64)
>> pts = np.array([[x,y,z] for x in K for y in K for z in K])
>> S = signed_distance(pts, v, f)
>> v, f = marching_cubes(S, pts, nx, ny, nz, 0.0)

)igl_Qu8mg5v7";

npe_function(marching_cubes)
npe_doc(ds_marching_cubes)
npe_arg(s, dense_float, dense_double)
npe_arg(gv, dense_float, dense_double)
npe_arg(nx, int)
npe_arg(ny, int)
npe_arg(nz, int)
npe_default_arg(isovalue, double, 0.0)

npe_begin_code()
    // input checks
    assert_rows_match(s, gv, "S", "GV");
    assert_cols_equals(s, 1, "S");
    assert_cols_equals(gv, 3, "GV");

    // vertices and faces of marched iso surface
    Eigen::MatrixXd SV;
    Eigen::MatrixXi SF; 

    Eigen::MatrixXd s_copy = s.template cast<double>();
    Eigen::MatrixXd gv_copy = gv.template cast<double>();

    igl::marching_cubes(s_copy, gv_copy, nx, ny, nz, isovalue, SV, SF);

    EigenDenseLike<npe_Matrix_gv> svRowMajor = SV.template cast<typename npe_Matrix_gv::Scalar>();
    EigenDenseLike<EigenDenseInt> sfRowMajor = SF.template cast<typename EigenDenseInt::Scalar>();

    return std::make_tuple(npe::move(svRowMajor), npe::move(sfRowMajor));
npe_end_code()