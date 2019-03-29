#include <npe.h>
#include <typedefs.h>






#include <igl/nrosy.h>

const char* ds_nrosy = R"igl_Qu8mg5v7(

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

 Generate a N-RoSy field from a sparse set of constraints
    
     Inputs:
       V       #V by 3 list of mesh vertex coordinates
       F       #F by 3 list of mesh faces (must be triangles)
       b       #B by 1 list of constrained face indices
       bc      #B by 3 list of representative vectors for the constrained
         faces
       b_soft  #S by 1 b for soft constraints
       w_soft  #S by 1 weight for the soft constraints (0-1)
       bc_soft #S by 3 bc for soft constraints
       N       the degree of the N-RoSy vector field
       soft    the strength of the soft constraints w.r.t. smoothness
               (0 -> smoothness only, 1->constraints only)
     Outputs:
       R       #F by 3 the representative vectors of the interpolated field
       S       #V by 1 the singularity index for each vertex (0 = regular)
)igl_Qu8mg5v7";

npe_function(nrosy)
npe_doc(ds_nrosy)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(b, Eigen::VectorXi &)
npe_arg(bc, Eigen::MatrixXd &)
npe_arg(b_soft, Eigen::VectorXi &)
npe_arg(w_soft, Eigen::VectorXd &)
npe_arg(bc_soft, Eigen::MatrixXd &)
npe_arg(n, int)
npe_arg(soft, double)


npe_begin_code()

  Eigen::MatrixXd & r;
  Eigen::VectorXd & s;
  igl::  copyleft::  comiso::nrosy(v, f, b, bc, b_soft, w_soft, bc_soft, n, soft, r, s);
  return std::make_tuple(npe::move(r), npe::move(s));

npe_end_code()
#include <igl/nrosy.h>

const char* ds_nrosy = R"igl_Qu8mg5v7(

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

wrapper for the case without soft constraints
)igl_Qu8mg5v7";

npe_function(nrosy)
npe_doc(ds_nrosy)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(b, Eigen::VectorXi &)
npe_arg(bc, Eigen::MatrixXd &)
npe_arg(n, int)


npe_begin_code()

  Eigen::MatrixXd & r;
  Eigen::VectorXd & s;
  igl::  copyleft::  comiso::nrosy(v, f, b, bc, n, r, s);
  return std::make_tuple(npe::move(r), npe::move(s));

npe_end_code()


