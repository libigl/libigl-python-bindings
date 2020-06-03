#include <npe.h>
#include <typedefs.h>
#include <igl/outer_hull.h>

const char* ds_outer_hull = R"igl_Qu8mg5v7(

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

 Compute the "outer hull" of a piecewise constant winding number induce
       triangle mesh (V,F).
      
       Inputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices into V
       Outputs:
         HV  #HV by 3 list of output vertex positions
         HF  #HF by 3 list of output triangle indices into HV
         J  #HF list of indices into F
         flip  #HF list of whether facet was flipped when added to HF
      
)igl_Qu8mg5v7";

npe_function(outer_hull)
npe_doc(ds_outer_hull)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenDense<npe_Scalar_> hv;
  EigenDense<npe_Scalar_> hf;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> flip;
  igl::  copyleft::  cgal::outer_hull(v, f, hv, hf, j, flip);
  return std::make_tuple(npe::move(hv), npe::move(hf), npe::move(j), npe::move(flip));

npe_end_code()
#include <igl/outer_hull_legacy.h>

const char* ds_outer_hull_legacy = R"igl_Qu8mg5v7(

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

 Compute the "outer hull" of a potentially non-manifold mesh (V,F) whose
       intersections have been "resolved" (e.g. using `cork` or
       `igl::copyleft::cgal::selfintersect`). The outer hull is defined to be all facets
       (regardless of orientation) for which there exists some path from infinity
       to the face without intersecting any other facets. For solids, this is the
       surface of the solid. In general this includes any thin "wings" or
       "flaps".  This implementation largely follows Section 3.6 of "Direct
       repair of self-intersecting meshes" [Attene 2014].
      
       Note: This doesn't require the input mesh to be piecewise constant
       winding number, but won't handle multiple non-nested connected
       components.
      
       Inputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices into V
       Outputs:
         G  #G by 3 list of output triangle indices into V
         J  #G list of indices into F
         flip  #F list of whether facet was added to G **and** flipped orientation
           (false for faces not added to G)
)igl_Qu8mg5v7";

npe_function(outer_hull_legacy)
npe_doc(ds_outer_hull_legacy)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenDense<npe_Scalar_> g;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> flip;
  igl::  copyleft::  cgal::outer_hull_legacy(v, f, g, j, flip);
  return std::make_tuple(npe::move(g), npe::move(j), npe::move(flip));

npe_end_code()


