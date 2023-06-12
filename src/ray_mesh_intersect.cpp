// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>

#include <igl/ray_mesh_intersect.h>
#include <pybind11/stl.h>

const char *ds_ray_mesh_intersect = R"igl_Qu8mg5v7(
Shoot a ray against a mesh (V,F) and collect the first hit.

Parameters
----------
source  3-vector origin of ray
dir  3-vector direction of ray
V  #V by 3 list of mesh vertex positions
F  #F by 3 list of mesh face indices into V

Returns
-------
hits  **sorted** list of hits: id, gid, u, v, t

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(ray_mesh_intersect)
npe_doc(ds_ray_mesh_intersect)

npe_arg(source, dense_float, dense_double)
npe_arg(dir, npe_matches(source))
npe_arg(v, npe_matches(source))
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_size_equals(source, 3, "source");
  assert_size_equals(dir, 3, "dir");
  assert_valid_3d_tri_mesh(v, f);

  std::vector<igl::Hit> hits;
  igl::ray_mesh_intersect(source, dir, v, f, hits);
  std::vector<std::tuple<int, int, float, float, float>> hits_res;

  for(const auto &h : hits)
    hits_res.emplace_back(h.id, h.gid, h.u, h.v, h.t);

  return hits_res;

npe_end_code()


// const char* ds_ray_mesh_intersect = R"igl_Qu8mg5v7(

// Parameters
// ----------


// Returns
// -------


// See also
// --------


// Notes
// -----
// None

// Examples
// --------

//  Outputs:

// )igl_Qu8mg5v7";

// npe_function(ray_mesh_intersect)
// npe_doc(ds_ray_mesh_intersect)

// npe_arg(source, dense_float, dense_double)
// npe_arg(dir, dense_float, dense_double)
// npe_arg(v, dense_float, dense_double)
// npe_arg(f, dense_int, dense_long)


// npe_begin_code()

//   igl::Hit & hit;
//   igl::ray_mesh_intersect(source, dir, v, f, hit);
//   return npe::move(hit);

// npe_end_code()
