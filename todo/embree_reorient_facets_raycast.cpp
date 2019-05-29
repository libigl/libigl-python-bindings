#include <npe.h>
#include <typedefs.h>
#include <igl/reorient_facets_raycast.h>

const char* ds_reorient_facets_raycast = R"igl_Qu8mg5v7(

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

 Orient each component (identified by C) of a mesh (V,F) using ambient
     occlusion such that the front side is less occluded than back side, as
     described in "A Simple Method for Correcting Facet Orientations in
     Polygon Meshes Based on Ray Casting" [Takayama et al. 2014].
    
     Inputs:
       V  #V by 3 list of vertex positions
       F  #F by 3 list of triangle indices
       rays_total  Total number of rays that will be shot
       rays_minimum  Minimum number of rays that each patch should receive
       facet_wise  Decision made for each face independently, no use of patches
         (i.e., each face is treated as a patch)
       use_parity  Use parity mode
       is_verbose  Verbose output to cout
     Outputs:
       I  #F list of whether face has been flipped
       C  #F list of patch ID (output of bfs_orient > manifold patches)
)igl_Qu8mg5v7";

npe_function(reorient_facets_raycast)
npe_doc(ds_reorient_facets_raycast)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  int rays_total;
  int rays_minimum;
  bool facet_wise;
  bool use_parity;
  bool is_verbose;
  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> c;
  igl::  embree::reorient_facets_raycast(v, f, rays_total, rays_minimum, facet_wise, use_parity, is_verbose, i, c);
  return std::make_tuple(npe::move(rays_total), npe::move(rays_minimum), npe::move(facet_wise), npe::move(use_parity), npe::move(is_verbose), npe::move(i), npe::move(c));

npe_end_code()
#include <igl/reorient_facets_raycast.h>

const char* ds_reorient_facets_raycast = R"igl_Qu8mg5v7(

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

 Outputs:
       FF  #F by 3 list of reoriented faces
     Defaults:
       rays_total = F.rows()*100;
       rays_minimum = 10;
       facet_wise = false;
       use_parity = false;
       is_verbose = false;
)igl_Qu8mg5v7";

npe_function(reorient_facets_raycast)
npe_doc(ds_reorient_facets_raycast)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> i;
  igl::  embree::reorient_facets_raycast(v, f, ff, i);
  return std::make_tuple(npe::move(ff), npe::move(i));

npe_end_code()


