// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/harmonic.h>

const char* ds_harmonic_w = R"igl_Qu8mg5v7(
Compute k-harmonic weight functions "coordinates".

Parameters
----------
     V  #V by dim vertex positions
     F  #F by simplex-size list of element indices
     b  #b boundary indices into V
     bc #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
    W  #V by #W list of weights

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic)
npe_doc(ds_harmonic_w)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(b, npe_matches(f))
npe_arg(bc, npe_matches(v))
npe_arg(k, int)

npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  assert_nonzero_rows(bc, "bc");
  assert_rows_match(b, bc, "b", "bc");
  EigenDenseLike<npe_Matrix_v> w;
  igl::harmonic(v, f, b, bc, k, w);
  return npe::move(w);

npe_end_code()
#include <igl/harmonic.h>


const char* ds_harmonic_ul = R"igl_Qu8mg5v7(

Compute harmonic map using uniform laplacian operator

Parameters
----------
     F  #F by simplex-size list of element indices
     b  #b boundary indices into V
     bc #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
    W  #V by #W list of weights

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic_uniform_laplacian)
npe_doc(ds_harmonic_ul)

npe_arg(f, dense_int32, dense_int64)
npe_arg(b, npe_matches(f))
npe_arg(bc, dense_float, dense_double)
npe_arg(k, int)


npe_begin_code()

  assert_valid_tet_or_tri_mesh_faces(f, "f");
  assert_nonzero_rows(bc, "bc");
  assert_rows_match(b, bc, "b", "bc");

  EigenDenseLike<npe_Matrix_bc> w;
  igl::harmonic(f, b, bc, k, w);
  return npe::move(w);

npe_end_code()






#include <igl/harmonic.h>

const char* ds_harmonic = R"igl_Qu8mg5v7(

Compute a harmonic map using a given Laplacian and mass matrix

Parameters
----------
     L  #V by #V discrete (integrated) Laplacian
     M  #V by #V mass matrix
     b  #b boundary indices into V
     bc  #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
  W  #V by #V list of weights

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic_from_laplacian_and_mass)
npe_doc(ds_harmonic)
//TODO: l and bc need to have same type, matching missing
npe_arg(l, sparse_float, sparse_double)
npe_arg(m, npe_matches(l))
npe_arg(b, dense_int32, dense_int64)
npe_arg(bc, dense_float, dense_double)
// npe_arg(bc, npe_dense_like(l))
npe_arg(k, int)


npe_begin_code()

  assert_shapes_match(l, m, "l", "m");
  assert_nonzero_rows(l, "l");
  assert_nonzero_rows(bc, "bc");
  assert_rows_match(b, bc, "b", "bc");

  Eigen::Matrix<typename npe_Matrix_l::Scalar, Eigen::Dynamic, Eigen::Dynamic> bc_copy = bc.template cast<typename npe_Matrix_l::Scalar>();

  Eigen::Matrix<typename npe_Matrix_l::Scalar, Eigen::Dynamic, Eigen::Dynamic, npe_Matrix_bc::Options> w;
  igl::harmonic(l, m, b, bc_copy, k, w);
  return npe::move(w);

npe_end_code()
#include <igl/harmonic.h>

const char* ds_harmonic_int_lapl = R"igl_Qu8mg5v7(

 Build the discrete k-harmonic operator (computing integrated quantities).
   That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x


Parameters
----------
     L  #V by #V discrete (integrated) Laplacian
     M  #V by #V mass matrix
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
    Q  #V by #V discrete (integrated) k-Laplacian
See also
--------


Notes
-----
Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic_integrated_from_laplacian_and_mass)
npe_doc(ds_harmonic_int_lapl)

npe_arg(l, sparse_float, sparse_double)
npe_arg(m, npe_matches(l))
npe_arg(k, int)


npe_begin_code()
  assert_shapes_match(l, m, "l", "m");
  assert_nonzero_rows(l, "l");
  EigenSparseLike<npe_Matrix_l> q;
  igl::harmonic(l, m, k, q);
  return npe::move(q);

npe_end_code()
#include <igl/harmonic.h>

const char* ds_harmonic_int = R"igl_Qu8mg5v7(

Parameters
----------
   V  #V by dim vertex positions
     F  #F by simplex-size list of element indices
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
    Q  #V by #V discrete (integrated) k-Laplacian

See also
--------


Notes
-----


Examples
--------


)igl_Qu8mg5v7";

npe_function(harmonic_integrated)
npe_doc(ds_harmonic_int)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int32, dense_int64)
npe_arg(k, int)


npe_begin_code()

  assert_valid_tet_or_tri_mesh(v, f);
  EigenSparseLike<npe_Matrix_v> q;
  igl::harmonic(v, f, k, q);
  return npe::move(q);

npe_end_code()


