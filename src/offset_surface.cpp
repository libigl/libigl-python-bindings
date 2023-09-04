// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
//TODO: __example
// TODO: remove __copy
// copy is necessary since the winding number only supports matrices

#include <common.h>
#include <igl/offset_surface.h>
#include <npe.h>
#include <typedefs.h>

const char *ds_offset_surface = R"igl_Qu8mg5v7(
Compute a triangulated offset surface using marching cubes on a grid of
signed distance values from the input triangle mesh.

Parameters
----------
   V  #V by 3 list of mesh vertex positions
   F  #F by 3 list of mesh triangle indices into V
   isolevel  iso level to extract (signed distance: negative inside)
   s  number of grid cells along longest side (controls resolution)
   signed_distance_type  type of signing to use one of SIGNED_DISTANCE_TYPE_PSEUDONORMAL, SIGNED_DISTANCE_TYPE_WINDING_NUMBER, SIGNED_DISTANCE_TYPE_DEFAULT, SIGNED_DISTANCE_TYPE_UNSIGNED, SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER

Returns
-------
   SV  #SV by 3 list of output surface mesh vertex positions
   SF  #SF by 3 list of output mesh triangle indices into SV
   GV  #GV=side(0)*side(1)*side(2) by 3 list of grid cell centers
   side  list of number of grid cells in x, y, and z directions
   So  #GV by 3 list of signed distance values _near_ `isolevel` ("far" from `isolevel` these values are incorrect)

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(offset_surface)
npe_doc(ds_offset_surface)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(isolevel, double)
npe_arg(s, int)
npe_arg(signed_distance_type, int)
npe_begin_code()
    assert_valid_3d_tri_mesh(v, f);

    // Alec: I don't understand why all these copies are needed here.
    Eigen::MatrixXd v_copy = v.template cast<double>();
    Eigen::MatrixXi f_copy = f.template cast<int>();

    Eigen::MatrixXd sv_copy;
    Eigen::MatrixXi sf_copy;
    Eigen::MatrixXd gv_copy;
    Eigen::MatrixXi side_copy;
    Eigen::MatrixXd so_copy;

    igl::offset_surface(v_copy, f_copy, isolevel, s, igl::SignedDistanceType(signed_distance_type), sv_copy, sf_copy, gv_copy, side_copy, so_copy);

    EigenDenseLike<npe_Matrix_v> sv = sv_copy.template cast<typename npe_Matrix_v::Scalar>();
    EigenDenseLike<npe_Matrix_f> sf = sf_copy.template cast<typename npe_Matrix_f::Scalar>();
    EigenDenseLike<npe_Matrix_v> gv = gv_copy.template cast<typename npe_Matrix_v::Scalar>();
    EigenDenseLike<npe_Matrix_f> side = side_copy.template cast<typename npe_Matrix_f::Scalar>();
    EigenDenseLike<npe_Matrix_f> so = so_copy.template cast<typename npe_Matrix_f::Scalar>();

    return std::make_tuple(npe::move(sv), npe::move(sf), npe::move(gv), npe::move(side), npe::move(so));

npe_end_code()
