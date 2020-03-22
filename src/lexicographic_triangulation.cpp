#include <npe.h>
#include <common.h>
#include <typedefs.h>

#include <igl/predicates/predicates.h>
#include <igl/lexicographic_triangulation.h>


const char *ds_lexicographic_triangulation = R"igl_Qu8mg5v7(

Given a set of points in 2D, return a lexicographic triangulation of these points.

Parameters
----------
P  #P by 2 list of vertex positions

Returns
-------
F  #F by 3 of faces in lexicographic triangulation.

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(lexicographic_triangulation)
npe_doc(ds_lexicographic_triangulation)

npe_arg(p, dense_float, dense_double)


npe_begin_code()
  assert_cols_equals(p, 2, "p");
  assert_nonzero_rows(p, "p");

  Eigen::MatrixXd p_copy = p.template cast<double>();

  igl::predicates::exactinit();

  const auto orient = [](
      const double *a,
      const double *b,
      const double *c)
      {
        return (int)igl::predicates::orient2d(
          Eigen::Vector2d(a[0], a[1]),
          Eigen::Vector2d(b[0], b[1]),
          Eigen::Vector2d(c[0], c[1])
        );
      };

  Eigen::MatrixXi f_copy;
  igl::lexicographic_triangulation(p_copy, orient, f_copy);
  EigenDenseInt f = f_copy.template cast < typename EigenDenseInt::Scalar>();
  return npe::move(f);

npe_end_code()


