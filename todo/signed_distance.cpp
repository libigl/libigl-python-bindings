#include <npe.h>
#include <typedefs.h>
#include <igl/signed_distance.h>

const char* ds_signed_distance = R"igl_Qu8mg5v7(

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

 Default bounds
)igl_Qu8mg5v7";

npe_function(signed_distance)
npe_doc(ds_signed_distance)

npe_arg(p, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(sign_type, igl::SignedDistanceType)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> n;
  igl::signed_distance(p, v, f, sign_type, s, i, c, n);
  return std::make_tuple(npe::move(s), npe::move(i), npe::move(c), npe::move(n));

npe_end_code()






#include <igl/signed_distance.h>

const char* ds_signed_distance = R"igl_Qu8mg5v7(

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

 Computes signed distance to a mesh
  
   Inputs:
     P  #P by 3 list of query point positions
     V  #V by 3 list of vertex positions
     F  #F by ss list of triangle indices, ss should be 3 unless sign_type ==
       SIGNED_DISTANCE_TYPE_UNSIGNED
     sign_type  method for computing distance _sign_ S
     lower_bound  lower bound of distances needed {std::numeric_limits::min}
     upper_bound  lower bound of distances needed {std::numeric_limits::max}
   Outputs:
     S  #P list of smallest signed distances
     I  #P list of facet indices corresponding to smallest distances
     C  #P by 3 list of closest points
     N  #P by 3 list of closest normals (only set if
       sign_type=SIGNED_DISTANCE_TYPE_PSEUDONORMAL)
  
   Known bugs: This only computes distances to triangles. So unreferenced
   vertices and degenerate triangles are ignored.
)igl_Qu8mg5v7";

npe_function(signed_distance)
npe_doc(ds_signed_distance)

npe_arg(p, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(sign_type, igl::SignedDistanceType)
npe_arg(lower_bound, typename DerivedV::Scalar)
npe_arg(upper_bound, typename DerivedV::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> n;
  igl::signed_distance(p, v, f, sign_type, lower_bound, upper_bound, s, i, c, n);
  return std::make_tuple(npe::move(s), npe::move(i), npe::move(c), npe::move(n));

npe_end_code()
#include <igl/signed_distance_pseudonormal.h>

const char* ds_signed_distance_pseudonormal = R"igl_Qu8mg5v7(

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

 Computes signed distance to mesh
  
   Inputs:
     tree  AABB acceleration tree (see AABB.h)
     F  #F by 3 list of triangle indices
     FN  #F by 3 list of triangle normals 
     VN  #V by 3 list of vertex normals (ANGLE WEIGHTING)
     EN  #E by 3 list of edge normals (UNIFORM WEIGHTING)
     EMAP  #F*3 mapping edges in F to E
     q  Query point
   Returns signed distance to mesh
  
)igl_Qu8mg5v7";

npe_function(signed_distance_pseudonormal)
npe_doc(ds_signed_distance_pseudonormal)

npe_arg(tree, AABB<DerivedV, 3> &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(fn, dense_f32, dense_f64)
npe_arg(vn, dense_f32, dense_f64)
npe_arg(en, dense_f32, dense_f64)
npe_arg(emap, dense_f32, dense_f64)
npe_arg(q, dense_f32, dense_f64)


npe_begin_code()

  igl::signed_distance_pseudonormal(tree, v, f, fn, vn, en, emap, q);
  return ;

npe_end_code()
#include <igl/signed_distance_pseudonormal.h>

const char* ds_signed_distance_pseudonormal = R"igl_Qu8mg5v7(
See signed_distance_pseudonormal for the documentation.
)igl_Qu8mg5v7";

npe_function(signed_distance_pseudonormal)
npe_doc(ds_signed_distance_pseudonormal)

npe_arg(p, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(tree, AABB<DerivedV, 3> &)
npe_arg(fn, dense_f32, dense_f64)
npe_arg(vn, dense_f32, dense_f64)
npe_arg(en, dense_f32, dense_f64)
npe_arg(emap, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> s;
  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> n;
  igl::signed_distance_pseudonormal(p, v, f, tree, fn, vn, en, emap, s, i, c, n);
  return std::make_tuple(npe::move(s), npe::move(i), npe::move(c), npe::move(n));

npe_end_code()
#include <igl/signed_distance_pseudonormal.h>

const char* ds_signed_distance_pseudonormal = R"igl_Qu8mg5v7(

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

 Outputs:
     s  sign
     sqrd  squared distance
     i  closest primitive
     c  closest point
     n  normal
)igl_Qu8mg5v7";

npe_function(signed_distance_pseudonormal)
npe_doc(ds_signed_distance_pseudonormal)

npe_arg(tree, AABB<DerivedV, 3> &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(fn, dense_f32, dense_f64)
npe_arg(vn, dense_f32, dense_f64)
npe_arg(en, dense_f32, dense_f64)
npe_arg(emap, dense_f32, dense_f64)
npe_arg(q, dense_f32, dense_f64)


npe_begin_code()

  Scalar & s;
  Scalar & sqrd;
  int & i;
  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> n;
  igl::signed_distance_pseudonormal(tree, v, f, fn, vn, en, emap, q, s, sqrd, i, c, n);
  return std::make_tuple(npe::move(s), npe::move(sqrd), npe::move(i), npe::move(c), npe::move(n));

npe_end_code()
#include <igl/signed_distance_pseudonormal.h>

const char* ds_signed_distance_pseudonormal = R"igl_Qu8mg5v7(
See signed_distance_pseudonormal for the documentation.
)igl_Qu8mg5v7";

npe_function(signed_distance_pseudonormal)
npe_doc(ds_signed_distance_pseudonormal)

npe_arg(tree, AABB<DerivedV, 2> &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(e, dense_f32, dense_f64)
npe_arg(en, dense_f32, dense_f64)
npe_arg(vn, dense_f32, dense_f64)
npe_arg(q, dense_f32, dense_f64)


npe_begin_code()

  Scalar & s;
  Scalar & sqrd;
  int & i;
  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> n;
  igl::signed_distance_pseudonormal(tree, v, e, en, vn, q, s, sqrd, i, c, n);
  return std::make_tuple(npe::move(s), npe::move(sqrd), npe::move(i), npe::move(c), npe::move(n));

npe_end_code()
#include <igl/signed_distance_winding_number.h>

const char* ds_signed_distance_winding_number = R"igl_Qu8mg5v7(

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
     tree  AABB acceleration tree (see cgal/point_mesh_squared_distance.h)
     hier  Winding number evaluation hierarchy
     q  Query point
   Returns signed distance to mesh
)igl_Qu8mg5v7";

npe_function(signed_distance_winding_number)
npe_doc(ds_signed_distance_winding_number)

npe_arg(tree, AABB<DerivedV, 3> &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(hier, igl::WindingNumberAABB<Derivedq, DerivedV, DerivedF> &)
npe_arg(q, dense_f32, dense_f64)


npe_begin_code()

  igl::signed_distance_winding_number(tree, v, f, hier, q);
  return ;

npe_end_code()
#include <igl/signed_distance_winding_number.h>

const char* ds_signed_distance_winding_number = R"igl_Qu8mg5v7(

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

 Outputs:
     s  sign
     sqrd  squared distance
     pp  closest point and primitve
)igl_Qu8mg5v7";

npe_function(signed_distance_winding_number)
npe_doc(ds_signed_distance_winding_number)

npe_arg(tree, AABB<DerivedV, 3> &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(hier, igl::WindingNumberAABB<Derivedq, DerivedV, DerivedF> &)
npe_arg(q, dense_f32, dense_f64)


npe_begin_code()

  Scalar & s;
  Scalar & sqrd;
  int & i;
  EigenDense<npe_Scalar_> c;
  igl::signed_distance_winding_number(tree, v, f, hier, q, s, sqrd, i, c);
  return std::make_tuple(npe::move(s), npe::move(sqrd), npe::move(i), npe::move(c));

npe_end_code()
#include <igl/signed_distance_winding_number.h>

const char* ds_signed_distance_winding_number = R"igl_Qu8mg5v7(
See signed_distance_winding_number for the documentation.
)igl_Qu8mg5v7";

npe_function(signed_distance_winding_number)
npe_doc(ds_signed_distance_winding_number)

npe_arg(tree, AABB<DerivedV, 2> &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(q, dense_f32, dense_f64)


npe_begin_code()

  Scalar & s;
  Scalar & sqrd;
  int & i;
  EigenDense<npe_Scalar_> c;
  igl::signed_distance_winding_number(tree, v, f, q, s, sqrd, i, c);
  return std::make_tuple(npe::move(s), npe::move(sqrd), npe::move(i), npe::move(c));

npe_end_code()


