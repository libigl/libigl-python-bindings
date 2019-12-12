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

  Eigen::MatrixXd v_copy = v.template cast<double>();

  const auto orient2_d = [](const double *pa, const double *pb, const double *pc) {
    Eigen::Vector2d pav; pav << pa[0], pa[1];
    Eigen::Vector2d pbv; pbv << pb[0], pb[1];
    Eigen::Vector2d pcv; pcv << pc[0], pc[1];
    return int(igl::predicates::orient2d(pav, pbv, pcv));
    };
  const auto incircle = [](const double *pa, const double *pb, const double *pc, const double *pd) {
    Eigen::Vector2d pav; pav << pa[0], pa[1];
    Eigen::Vector2d pbv; pbv << pb[0], pb[1];
    Eigen::Vector2d pcv; pcv << pc[0], pc[1];
    Eigen::Vector2d pdv; pdv << pd[0], pd[1];
    return int(igl::predicates::incircle(pav, pbv, pcv, pdv));
    };

  Eigen::MatrixXi f_copy;
  igl::delaunay_triangulation(v_copy, orient2_d, incircle, f_copy);
  EigenDenseInt f = f_copy.template cast<typename EigenDenseInt::Scalar>();
  return npe::move(f);

npe_end_code()


