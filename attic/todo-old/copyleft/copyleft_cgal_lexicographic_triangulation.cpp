#include <npe.h>
#include <typedefs.h>
#include <igl/lexicographic_triangulation.h>

const char* ds_lexicographic_triangulation = R"igl_Qu8mg5v7(

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

 Given a set of points in 2D, return a lexicographic triangulation of these
       points.
      
       Inputs:
         P  #P by 2 list of vertex positions
      
       Outputs:
         F  #F by 3 of faces in lexicographic triangulation.
)igl_Qu8mg5v7";

npe_function(lexicographic_triangulation)
npe_doc(ds_lexicographic_triangulation)

npe_arg(p, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> f;
  igl::  copyleft::  cgal::lexicographic_triangulation(p, f);
  return npe::move(f);

npe_end_code()


