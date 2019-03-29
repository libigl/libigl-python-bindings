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
     orient2D  A functor such that orient2D(pa, pb, pc) returns
                 1 if pa,pb,pc forms a conterclockwise triangle.
                -1 if pa,pb,pc forms a clockwise triangle.
                 0 if pa,pb,pc are collinear.
                where the argument pa,pb,pc are of type Scalar[2].
  
   Outputs:
     F  #F by 3 of faces in lexicographic triangulation.
)igl_Qu8mg5v7";

npe_function(lexicographic_triangulation)
npe_doc(ds_lexicographic_triangulation)

npe_arg(p, dense_f32, dense_f64)


npe_begin_code()

  Orient2D orient2_d;
  EigenDense<npe_Scalar_> f;
  igl::lexicographic_triangulation(p, orient2_d, f);
  return std::make_tuple(npe::move(orient2_d), npe::move(f));

npe_end_code()


