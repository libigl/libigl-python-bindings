#include <npe.h>
#include <typedefs.h>
#include <igl/delaunay_triangulation.h>

const char* ds_delaunay_triangulation = R"igl_Qu8mg5v7(

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

 Given a set of points in 2D, return a Delaunay triangulation of these
       points.
      
       Inputs:
         V  #V by 2 list of vertex positions
      
       Outputs:
         F  #F by 3 of faces in Delaunay triangulation.
)igl_Qu8mg5v7";

npe_function(delaunay_triangulation)
npe_doc(ds_delaunay_triangulation)

npe_arg(v, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> f;
  igl::  copyleft::  cgal::delaunay_triangulation(v, f);
  return npe::move(f);

npe_end_code()


