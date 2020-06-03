#include <npe.h>
#include <typedefs.h>






#include <igl/subdivide_segments.h>

const char* ds_subdivide_segments = R"igl_Qu8mg5v7(

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

 Insert steiner points to subdivide a given set of line segments
       
       Inputs:
         V  #V by 2 list of vertex positions
         E  #E by 2 list of segment indices into V
         steiner  #E list of lists of unsorted steiner points (including
           endpoints) along the #E original segments
       Outputs:
         VI  #VI by 2 list of output vertex positions, copies of V are always
           the first #V vertices
         EI  #EI by 2 list of segment indices into V, #EI ≥ #E
         J  #EI list of indices into E revealing "parent segments"
         IM  #VI list of indices into VV of unique vertices.
)igl_Qu8mg5v7";

npe_function(subdivide_segments)
npe_doc(ds_subdivide_segments)

npe_arg(v, dense_float, dense_double)
npe_arg(e, dense_float, dense_double)
npe_arg(steiner, std::vector<std::vector<CGAL::Point_2<Kernel> > > &)


npe_begin_code()

  EigenDense<npe_Scalar_> vi;
  EigenDense<npe_Scalar_> ei;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> im;
  igl::  copyleft::  cgal::subdivide_segments(v, e, steiner, vi, ei, j, im);
  return std::make_tuple(npe::move(vi), npe::move(ei), npe::move(j), npe::move(im));

npe_end_code()


