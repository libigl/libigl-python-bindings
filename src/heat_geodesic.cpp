#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/heat_geodesics.h>

const char *ds_heat_geodesic = R"igl_Qu8mg5v7xxx(
Compute fast approximate geodesic distances using precomputed data from a set of selected source vertices (gamma)

Parameters
----------
V  #V by dim list of mesh vertex positions
F  #F by 3 list of mesh face indices into V
t  "heat" parameter (smaller --> more accurate, less stable)
gamma  #gamma list of indices into V of source vertices

Returns
-------
D  #V list of distances to gamma

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7xxx";

npe_function(heat_geodesic)
npe_doc(ds_heat_geodesic)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(t, double)
npe_arg(gamma, npe_matches(f))

npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);

  EigenDenseLike<npe_Matrix_v> v_copy = v;
  EigenDenseLike<npe_Matrix_f> f_copy = f;
  EigenDenseLike<npe_Matrix_f> gamma_copy = gamma;

  Eigen::Matrix<npe_Scalar_v, Eigen::Dynamic, 1> d_copy;
  igl::HeatGeodesicsData<npe_Scalar_v> data;
  igl::heat_geodesics_precompute(v_copy, f_copy, npe_Scalar_v(t), data);
  igl::heat_geodesics_solve(data, gamma_copy, d_copy);
  EigenDenseLike<npe_Matrix_v> d = d_copy;

  return npe::move(d);

npe_end_code()


