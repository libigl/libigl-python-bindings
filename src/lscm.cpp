//TODO: __example
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/lscm.h>

const char* ds_lscm = R"igl_Qu8mg5v7(
Compute a Least-squares conformal map parametrization.

Parameters
----------
v : #v by 3 array of mesh vertex positions
f : #f by 3 array of mesh faces (must be triangles)
b : #b boundary indices into v
bc : #b by 3 list of boundary values

Returns
-------
uv #v by 2 list of 2D mesh vertex positions in UV space

See also
--------
None

Notes
-----
Derived in "Intrinsic Parameterizations of Surface Meshes" [Desbrun et al.
2002] and "Least Squares Conformal Maps for Automatic Texture Atlas
Generation" [Lévy et al. 2002]), though this implementation follows the
derivation in: "Spectral Conformal Parameterization" [Mullen et al. 2008]
(note, this does **not** implement the Eigen-decomposition based method in
[Mullen et al. 2008], which is not equivalent. Input should be a manifold
mesh (also no unreferenced vertices) and "boundary" (fixed vertices) `b`
should contain at least two vertices per connected component.
Returns true only on solver success.

Examples
--------

)igl_Qu8mg5v7";

npe_function(lscm)
npe_doc(ds_lscm)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(b, npe_matches(f))
npe_arg(bc, npe_matches(v))
npe_begin_code()

  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::VectorXi b_copy = b.template cast<int>();
  Eigen::MatrixXd bc_copy = bc.template cast<double>();
  Eigen::MatrixXd uv; //TODO: major
  bool success = igl::lscm(v_copy, f_copy, b_copy, bc_copy, uv);
  return std::make_tuple(success, npe::move(uv));

npe_end_code()


