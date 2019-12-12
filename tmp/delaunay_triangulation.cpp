#include <common.h>
#include <npe.h>
#include <typedefs.h>

#include <igl/predicates/predicates.h>


#include <igl/delaunay_triangulation.h>

const char *ds_delaunay_triangulation = R"igl_Qu8mg5v7(
Given a set of points in 2D, return a Delaunay triangulation of these
   points.
Parameters
----------
V  #V by 2 list of vertex positions

Returns
-------
F  #F by 3 of faces in Delaunay triangulation.

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(delaunay_triangulation)
npe_doc(ds_delaunay_triangulation)

npe_arg(v, dense_float, dense_double)


npe_begin_code()
  assert_nonzero_rows(v, "v");
  assert_cols_equals(v, 2, "v");

  typedef Eigen::Matrix<typename npe_Matrix_v::Scalar, 1, 2> Point;

  const auto orient2_d = [](const Point &pa, const Point &pb, const Point &pc) { return igl::predicates::orient2d(pa, pb, pc); };
  const auto incircle = [](const Point &pa, const Point &pb, const Point &pc, const Point &pd) { return igl::predicates::incircle(pa, pb, pc, pd); };

  EigenDenseInt f;
  igl::delaunay_triangulation(v, orient2_d, incircle, f);
  return npe::move(f);

npe_end_code()


