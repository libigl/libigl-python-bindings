// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Francis Williams
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>


#include <igl/signed_distance.h>

const char *ds_signed_distance = R"igl_Qu8mg5v7(
SIGNED_DISTANCE computes signed distance to a mesh


Parameters
----------
     P  #P by 3 list of query point positions
     V  #V by 3 list of vertex positions
     F  #F by ss list of triangle indices, ss should be 3 unless sign_type
     sign_type (Optional, defaults to psuedo-normal) Sign type method for 
                     determining sign on signed distance
     return_normals  (Optional, defaults to False) If set to True, will return pseudonormals of
                     closest points to each query point in P
Returns
-------
    S  #P list of smallest signed distances
    I  #P list of facet indices corresponding to smallest distances
    C  #P by 3 list of closest points

See also
--------


Notes
-----
    Known issue: This only computes distances to triangles. So unreferenced
    vertices and degenerate triangles are ignored.

Examples
--------
>>> S, I, C = signed_distance(P, V, F, sign_type=igl.SIGNED_DISTANCE_TYPE_FAST_WINDING_NUMBER, return_normals=False)
>>> S, I, C, N = signed_distance(P, V, F, return_normals=True)

)igl_Qu8mg5v7";

npe_function(signed_distance)
npe_doc(ds_signed_distance)

npe_arg(p, dense_float, dense_double)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_default_arg(sign_type, int, int(igl::SIGNED_DISTANCE_TYPE_DEFAULT))
npe_default_arg(return_normals, bool, false)

npe_begin_code()
    assert_cols_equals(p, 3, "p");
    assert_nonzero_rows(p, "p");
    assert_valid_3d_tri_mesh(v, f, "v", "f");

    // ensure valid sign_type given
    if ((sign_type < 0) || (sign_type > igl::NUM_SIGNED_DISTANCE_TYPE)) {
        //NOTE: compiler concats adjacent string literals. 
        throw pybind11::value_error(
            "Parameter sign_type invalid, must be one of:"
            "\n\t0: Use fast pseudo-normal test [Bærentzen & Aanæs 2005]"
            "\n\t1: Use winding number [Jacobson, Kavan Sorking-Hornug 2013]"
            "\n\t2: Default (pseudo-normal)"
            "\n\t3: Unsigned"
            "\n\t4: Use Fast winding number [Barill, Dickson, Schmidt, Levin, Jacobson 2018]\n"
        );
    }

    //Ensure if normals requested, sign type is also SIGNED_DISTANCE_TYPE_PSEUDONORMAL
    if (return_normals) {
        // note: if sign_type is default, we assume they don't care and switch to pseudonormal!
        if (sign_type == igl::SIGNED_DISTANCE_TYPE_DEFAULT) {
            sign_type = igl::SIGNED_DISTANCE_TYPE_PSEUDONORMAL;
        } else if (sign_type != igl::SIGNED_DISTANCE_TYPE_PSEUDONORMAL ) {
            throw pybind11::value_error("Parameter sign_type must be SIGNED_DISTANCE_TYPE_PSEUDONORMAL for normals to be returned. Or return_normals should be false.");
        }
    }

    Eigen::MatrixXd V = v.template cast<double>();
    Eigen::MatrixXd P = p.template cast<double>();
    Eigen::MatrixXi F = f.template cast<int>();

    EigenDenseLike<npe_Matrix_p> S;
    Eigen::Matrix<npe_Scalar_f, Eigen::Dynamic, 1> I;
    EigenDenseLike<npe_Matrix_v> C;
    EigenDenseLike<npe_Matrix_v> N;

    if (return_normals) {
        igl::signed_distance(P, V, F, igl::SIGNED_DISTANCE_TYPE_PSEUDONORMAL, S, I, C, N);
        return pybind11::make_tuple(npe::move(S), npe::move(I), npe::move(C), npe::move(N));
    } else {
        // N is only populated when sign_type == SIGNED_DISTANCE_TYPE_PSEUDONORMAL
        igl::signed_distance(P, V, F, static_cast<igl::SignedDistanceType>(sign_type), S, I, C, N);
        return pybind11::make_tuple(npe::move(S), npe::move(I), npe::move(C));
    }

npe_end_code()



