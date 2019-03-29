#include <npe.h>
#include <typedefs.h>






#include <igl/hausdorff.h>

const char* ds_hausdorff = R"igl_Qu8mg5v7(

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

 HAUSDORFF compute the Hausdorff distance between mesh (VA,FA) and mesh
   (VB,FB). This is the 
  
   d(A,B) = max ( max min d(a,b) , max min d(b,a) )
                  a∈A b∈B          b∈B a∈A
  
   Known issue: This is only computing max(min(va,B),min(vb,A)). This is
   better than max(min(va,Vb),min(vb,Va)). This (at least) is missing
   "edge-edge" cases like the distance between the two different
   triangulations of a non-planar quad in 3D. Even simpler, consider the
   Hausdorff distance between the non-convex, block letter V polygon (with 7
   vertices) in 2D and its convex hull. The Hausdorff distance is defined by
   the midpoint in the middle of the segment across the concavity and some
   non-vertex point _on the edge_ of the V.
  
   Inputs:
     VA  #VA by 3 list of vertex positions
     FA  #FA by 3 list of face indices into VA
     VB  #VB by 3 list of vertex positions
     FB  #FB by 3 list of face indices into VB
   Outputs:
     d  hausdorff distance
     pair  2 by 3 list of "determiner points" so that pair(1,:) is from A
       and pair(2,:) is from B
  
)igl_Qu8mg5v7";

npe_function(hausdorff)
npe_doc(ds_hausdorff)

npe_arg(va, dense_f32, dense_f64)
npe_arg(fa, dense_f32, dense_f64)
npe_arg(vb, dense_f32, dense_f64)
npe_arg(fb, dense_f32, dense_f64)


npe_begin_code()

  Scalar & d;
  igl::hausdorff(va, fa, vb, fb, d);
  return npe::move(d);

npe_end_code()
#include <igl/hausdorff.h>

const char* ds_hausdorff = R"igl_Qu8mg5v7(

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

 Compute lower and upper bounds (l,u) on the Hausdorff distance between a triangle
   (V) and a pointset (e.g., mesh, triangle soup) given by a distance function
   handle (dist_to_B).
  
   Inputs:
     V   3 by 3 list of corner positions so that V.row(i) is the position of the
       ith corner
     dist_to_B  function taking the x,y,z coordinate of a query position and
       outputting the closest-point distance to some point-set B
   Outputs:
     l  lower bound on Hausdorff distance 
     u  upper bound on Hausdorff distance
  
)igl_Qu8mg5v7";

npe_function(hausdorff)
npe_doc(ds_hausdorff)

npe_arg(v, dense_f32, dense_f64)
npe_arg(dist_to_b, std::function<Scalar (const Scalar &, const Scalar &, const Scalar &)> &)


npe_begin_code()

  Scalar & l;
  Scalar & u;
  igl::hausdorff(v, dist_to_b, l, u);
  return std::make_tuple(npe::move(l), npe::move(u));

npe_end_code()


