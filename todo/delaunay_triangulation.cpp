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
     orient2D  A functor such that orient2D(pa, pb, pc) returns
                 1 if pa,pb,pc forms a conterclockwise triangle.
                -1 if pa,pb,pc forms a clockwise triangle.
                 0 if pa,pb,pc are collinear.
                where the argument pa,pb,pc are of type Scalar[2].
     incircle  A functor such that incircle(pa, pb, pc, pd) returns
                 1 if pd is on the positive size of circumcirle of (pa,pb,pc)
                -1 if pd is on the positive size of circumcirle of (pa,pb,pc)
                 0 if pd is cocircular with pa, pb, pc.
   Outputs:
     F  #F by 3 of faces in Delaunay triangulation.
)igl_Qu8mg5v7";

npe_function(delaunay_triangulation)
npe_doc(ds_delaunay_triangulation)

npe_arg(v, dense_f32, dense_f64)


npe_begin_code()

  Orient2D orient2_d;
  InCircle incircle;
  EigenDense<npe_Scalar_> f;
  igl::delaunay_triangulation(v, orient2_d, incircle, f);
  return std::make_tuple(npe::move(orient2_d), npe::move(incircle), npe::move(f));

npe_end_code()


