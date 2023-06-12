// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <common.h>
#include <typedefs.h>
#include <igl/project_to_line_segment.h>

const char *ds_project_to_line_segment = R"igl_Qu8mg5v7(
PROJECT_TO_LINE_SEGMENT project points onto vectors, that is find the parameter
   t for a point p such that proj_p = (y-x).*t, additionally compute the
   squared distance from p to the line of the vector, such that
   |p - proj_p|² = sqr_d


Parameters
----------
P  #P by dim list of points to be projected
S  size dim start position of line vector
D  size dim destination position of line vector

Returns
-------
T  #P by 1 list of parameters
sqrD  #P by 1 list of squared distances

See also
--------


Notes
-----
None

Examples
--------
   [T,sqrD] = project_to_line_segment(P,S,D)

)igl_Qu8mg5v7";

npe_function(project_to_line_segment)
npe_doc(ds_project_to_line_segment)

npe_arg(p, dense_float, dense_double)
npe_arg(s, npe_matches(p))
npe_arg(d, npe_matches(p))


npe_begin_code()
  assert_nonzero_rows(p, "p");
  assert_size_equals(s, p.cols(), "s");
  assert_size_equals(d, p.cols(), "d");

  typedef Eigen::Matrix<npe_Scalar_p, 1, Eigen::Dynamic> Mat;
  Mat s_copy(s.size());
  Mat d_copy(d.size());

  for (int i = 0; i < s.size(); ++i)
  {
    if (s.cols() == 1)
      s_copy[i] = s(i, 0);
    else
      s_copy[i] = s(0, i);

    if (d.cols() == 1)
      d_copy[i] = d(i, 0);
    else
      d_copy[i] = d(0, i);
  }

  Eigen::Matrix<npe_Scalar_p, Eigen::Dynamic, Eigen::Dynamic> p_copy = p;

  EigenDense<npe_Scalar_p> t;
  EigenDense<npe_Scalar_p> sqr_d;

  igl::project_to_line_segment(p_copy, s_copy, d_copy, t, sqr_d);
  return std::make_tuple(npe::move(t), npe::move(sqr_d));

npe_end_code()


