#include <npe.h>
#include <typedefs.h>






#include <igl/offset_surface.h>

const char* ds_offset_surface = R"igl_Qu8mg5v7(

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

 Compute a triangulated offset surface using matching cubes on a grid of
     signed distance values from the input triangle mesh.
    
     Inputs:
       V  #V by 3 list of mesh vertex positions
       F  #F by 3 list of mesh triangle indices into V
       isolevel  iso level to extract (signed distance: negative inside)
       s  number of grid cells along longest side (controls resolution)
       signed_distance_type  type of signing to use (see
         ../signed_distance.h)
     Outputs:
       SV  #SV by 3 list of output surface mesh vertex positions
       SF  #SF by 3 list of output mesh triangle indices into SV
       GV  #GV=side(0)*side(1)*side(2) by 3 list of grid cell centers
       side  list of number of grid cells in x, y, and z directions
       S  #GV by 3 list of signed distance values _near_ `isolevel` ("far"
         from `isolevel` these values are incorrect)
    
)igl_Qu8mg5v7";

npe_function(offset_surface)
npe_doc(ds_offset_surface)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(isolevel, isolevelType)
npe_arg(s, typename Derivedside::Scalar)
npe_arg(signed_distance_type, igl::SignedDistanceType &)


npe_begin_code()

  EigenDense<npe_Scalar_> sv;
  EigenDense<npe_Scalar_> sf;
  EigenDense<npe_Scalar_> gv;
  EigenDense<npe_Scalar_> side;
  EigenDense<npe_Scalar_> s;
  igl::  copyleft::offset_surface(v, f, isolevel, s, signed_distance_type, sv, sf, gv, side, s);
  return std::make_tuple(npe::move(sv), npe::move(sf), npe::move(gv), npe::move(side), npe::move(s));

npe_end_code()


