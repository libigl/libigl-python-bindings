#include <npe.h>
#include <typedefs.h>
#include <igl/peel_outer_hull_layers.h>

const char* ds_peel_outer_hull_layers = R"igl_Qu8mg5v7(

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

 Computes necessary generic information for boolean operations by
       successively "peeling" off the "outer hull" of a mesh (V,F) resulting from
       "resolving" all (self-)intersections.
      
       Inputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices into V
       Outputs:
         I  #F list of which peel Iation a facet belongs 
         flip  #F list of whether a facet's orientation was flipped when facet
           "peeled" into its associated outer hull layer.
       Returns number of peels
)igl_Qu8mg5v7";

npe_function(peel_outer_hull_layers)
npe_doc(ds_peel_outer_hull_layers)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> flip;
  igl::  copyleft::  cgal::peel_outer_hull_layers(v, f, i, flip);
  return std::make_tuple(npe::move(i), npe::move(flip));

npe_end_code()


