#include <npe.h>
#include <typedefs.h>
#include <igl/is_delaunay.h>

const char* ds_is_delaunay = R"igl_Qu8mg5v7(

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

 IS_DELAUNAY Determine if each edge in the mesh (V,F) is Delaunay.
  
   Inputs:
     V  #V by dim list of vertex positions
     F  #F by 3 list of triangles indices
   Outputs:
     D  #F by 3 list of bools revealing whether edges corresponding 23 31 12
       are locally Delaunay. Boundary edges are by definition Delaunay.
       Non-Manifold edges are by definition not Delaunay.
)igl_Qu8mg5v7";

npe_function(is_delaunay)
npe_doc(ds_is_delaunay)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> d;
  igl::is_delaunay(v, f, d);
  return npe::move(d);

npe_end_code()






#include <igl/is_delaunay.h>

const char* ds_is_delaunay = R"igl_Qu8mg5v7(

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

 Determine whether a single edge is Delaunay using a provided (extrinsic) incirle
   test.
  
   Inputs:
     V  #V by dim list of vertex positions
     F  #F by 3 list of triangles indices
     uE2E  #uE list of lists of indices into E of coexisting edges (see
       unique_edge_map)
     incircle  A functor such that incircle(pa, pb, pc, pd) returns
                 1 if pd is on the positive size of circumcirle of (pa,pb,pc)
                -1 if pd is on the positive size of circumcirle of (pa,pb,pc)
                 0 if pd is cocircular with pa, pb, pc.
                 (see delaunay_triangulation)
     uei  index into uE2E of edge to check
   Returns true iff edge is Delaunay
)igl_Qu8mg5v7";

npe_function(is_delaunay)
npe_doc(ds_is_delaunay)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)
npe_arg(incircle, InCircle)
npe_arg(uei, ueiType)


npe_begin_code()

  igl::is_delaunay(v, f, u_e2_e, incircle, uei);
  return ;

npe_end_code()


