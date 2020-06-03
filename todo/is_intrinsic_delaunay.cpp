#include <npe.h>
#include <typedefs.h>
#include <igl/is_intrinsic_delaunay.h>

const char* ds_is_intrinsic_delaunay = R"igl_Qu8mg5v7(

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

 IS_INTRINSIC_DELAUNAY Determine if each edge in the mesh (V,F) is Delaunay.
  
   Inputs:
     l  #l by dim list of edge lengths
     F  #F by 3 list of triangles indices
   Outputs:
     D  #F by 3 list of bools revealing whether edges corresponding 23 31 12
       are locally Delaunay. Boundary edges are by definition Delaunay.
       Non-Manifold edges are by definition not Delaunay.
)igl_Qu8mg5v7";

npe_function(is_intrinsic_delaunay)
npe_doc(ds_is_intrinsic_delaunay)

npe_arg(l, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> d;
  igl::is_intrinsic_delaunay(l, f, d);
  return npe::move(d);

npe_end_code()






#include <igl/is_intrinsic_delaunay.h>

const char* ds_is_intrinsic_delaunay = R"igl_Qu8mg5v7(

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

 Inputs:
     uE2E  #uE list of lists mapping unique edges to (half-)edges
)igl_Qu8mg5v7";

npe_function(is_intrinsic_delaunay)
npe_doc(ds_is_intrinsic_delaunay)

npe_arg(l, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)


npe_begin_code()

  EigenDense<npe_Scalar_> d;
  igl::is_intrinsic_delaunay(l, f, u_e2_e, d);
  return npe::move(d);

npe_end_code()
#include <igl/is_intrinsic_delaunay.h>

const char* ds_is_intrinsic_delaunay = R"igl_Qu8mg5v7(

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
     l  #l by dim list of edge lengths
     uE2E  #uE list of lists of indices into E of coexisting edges (see
       unique_edge_map)
     num_faces  number of faces (==#F)
     uei  index into uE2E of edge to check
   Returns true iff edge is Delaunay
)igl_Qu8mg5v7";

npe_function(is_intrinsic_delaunay)
npe_doc(ds_is_intrinsic_delaunay)

npe_arg(l, dense_f32, dense_f64)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)
npe_arg(num_faces, Index)
npe_arg(uei, Index)


npe_begin_code()

  igl::is_intrinsic_delaunay(l, u_e2_e, num_faces, uei);
  return ;

npe_end_code()


