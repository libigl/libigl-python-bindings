#include <npe.h>
#include <typedefs.h>






#include <igl/lscm.h>

const char* ds_lscm = R"igl_Qu8mg5v7(

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

 Compute a Least-squares conformal map parametrization (equivalently
   derived in "Intrinsic Parameterizations of Surface Meshes" [Desbrun et al.
   2002] and "Least Squares Conformal Maps for Automatic Texture Atlas
   Generation" [Lévy et al. 2002]), though this implementation follows the
   derivation in: "Spectral Conformal Parameterization" [Mullen et al. 2008]
   (note, this does **not** implement the Eigen-decomposition based method in
   [Mullen et al. 2008], which is not equivalent). Input should be a manifold
   mesh (also no unreferenced vertices) and "boundary" (fixed vertices) `b`
   should contain at least two vertices per connected component.
  
   Inputs:
     V  #V by 3 list of mesh vertex positions
     F  #F by 3 list of mesh faces (must be triangles)
     b  #b boundary indices into V
     bc #b by 3 list of boundary values
   Outputs:
     UV #V by 2 list of 2D mesh vertex positions in UV space
   Returns true only on solver success.
  
)igl_Qu8mg5v7";

npe_function(lscm)
npe_doc(ds_lscm)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(b, Eigen::VectorXi &)
npe_arg(bc, Eigen::MatrixXd &)


npe_begin_code()

  Eigen::MatrixXd & v_uv;
  igl::lscm(v, f, b, bc, v_uv);
  return npe::move(v_uv);

npe_end_code()


