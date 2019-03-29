#include <npe.h>
#include <typedefs.h>
#include <igl/bijective_composite_harmonic_mapping.h>

const char* ds_bijective_composite_harmonic_mapping = R"igl_Qu8mg5v7(

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

 Compute a planar mapping of a triangulated polygon (V,F) subjected to
   boundary conditions (b,bc). The mapping should be bijective in the sense
   that no triangles' areas become negative (this assumes they started
   positive). This mapping is computed by "composing" harmonic mappings
   between incremental morphs of the boundary conditions. This is a bit like
   a discrete version of "Bijective Composite Mean Value Mappings" [Schneider
   et al. 2013] but with a discrete harmonic map (cf. harmonic coordinates)
   instead of mean value coordinates. This is inspired by "Embedding a
   triangular graph within a given boundary" [Xu et al. 2011].
  
   Inputs:
     V  #V by 2 list of triangle mesh vertex positions
     F  #F by 3 list of triangle indices into V
     b  #b list of boundary indices into V
     bc  #b by 2 list of boundary conditions corresponding to b
   Outputs:
     U  #V by 2 list of output mesh vertex locations
   Returns true if and only if U contains a successful bijectie mapping
  
   
)igl_Qu8mg5v7";

npe_function(bijective_composite_harmonic_mapping)
npe_doc(ds_bijective_composite_harmonic_mapping)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(b, dense_f32, dense_f64)
npe_arg(bc, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> u;
  igl::bijective_composite_harmonic_mapping(v, f, b, bc, u);
  return npe::move(u);

npe_end_code()
#include <igl/bijective_composite_harmonic_mapping.h>

const char* ds_bijective_composite_harmonic_mapping = R"igl_Qu8mg5v7(

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


   Inputs:
     min_steps  minimum number of steps to take from V(b,:) to bc
     max_steps  minimum number of steps to take from V(b,:) to bc (if
       max_steps == min_steps then no further number of steps will be tried)
     num_inner_iters  number of iterations of harmonic solves to run after
       for each morph step (to try to push flips back in)
     test_for_flips  whether to check if flips occurred (and trigger more
       steps). if test_for_flips = false then this function always returns
       true
   
)igl_Qu8mg5v7";

npe_function(bijective_composite_harmonic_mapping)
npe_doc(ds_bijective_composite_harmonic_mapping)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(b, dense_f32, dense_f64)
npe_arg(bc, dense_f32, dense_f64)
npe_arg(min_steps, int)
npe_arg(max_steps, int)
npe_arg(num_inner_iters, int)
npe_arg(test_for_flips, bool)


npe_begin_code()

  EigenDense<npe_Scalar_> u;
  igl::bijective_composite_harmonic_mapping(v, f, b, bc, min_steps, max_steps, num_inner_iters, test_for_flips, u);
  return npe::move(u);

npe_end_code()


