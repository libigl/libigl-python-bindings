#include <npe.h>
#include <typedefs.h>
#include <igl/snap_rounding.h>

const char* ds_snap_rounding = R"igl_Qu8mg5v7(

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

 SNAP_ROUNDING Snap a list of possible intersecting segments with
       endpoints in any precision to _the_ integer grid.
      
       Inputs:
         V  #V by 2 list of vertex positions
         E  #E by 2 list of segment indices into V
       Outputs:
         VI  #VI by 2 list of output integer vertex positions, rounded copies
           of V are always the first #V vertices
         EI  #EI by 2 list of segment indices into V, #EI ≥ #E
         J  #EI list of indices into E revealing "parent segments"
)igl_Qu8mg5v7";

npe_function(snap_rounding)
npe_doc(ds_snap_rounding)

npe_arg(v, dense_float, dense_double)
npe_arg(e, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> vi;
  EigenDense<npe_Scalar_> ei;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::snap_rounding(v, e, vi, ei, j);
  return std::make_tuple(npe::move(vi), npe::move(ei), npe::move(j));

npe_end_code()


