#include <npe.h>
#include <typedefs.h>






#include <igl/mesh_with_skeleton.h>

const char* ds_mesh_with_skeleton = R"igl_Qu8mg5v7(

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

 Mesh the interior of a given surface with tetrahedra which are graded
       (tend to be small near the surface and large inside) and conform to the
       given handles and samplings thereof.
      
       Inputs:
        V  #V by 3 list of mesh vertex positions
        F  #F by 3 list of triangle indices
        C  #C by 3 list of vertex positions
        P  #P list of point handle indices
        BE #BE by 2 list of bone-edge indices
        CE #CE by 2 list of cage-edge indices
        samples_per_bone  #samples to add per bone
        tetgen_flags  flags to pass to tetgen {""-->"pq2Y"} otherwise you're on
          your own and it's your funeral if you pass nonsense flags
       Outputs:
        VV  #VV by 3 list of tet-mesh vertex positions
        TT  #TT by 4 list of tetrahedra indices
        FF  #FF by 3 list of surface triangle indices
       Returns true only on success
)igl_Qu8mg5v7";

npe_function(mesh_with_skeleton)
npe_doc(ds_mesh_with_skeleton)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(c, Eigen::MatrixXd &)
npe_arg(, Eigen::VectorXi &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(ce, Eigen::MatrixXi &)
npe_arg(samples_per_bone, int)
npe_arg(tetgen_flags, std::string &)


npe_begin_code()

  Eigen::MatrixXd & vv;
  Eigen::MatrixXi & tt;
  Eigen::MatrixXi & ff;
  igl::  copyleft::  tetgen::mesh_with_skeleton(v, f, c, , be, ce, samples_per_bone, tetgen_flags, vv, tt, ff);
  return std::make_tuple(npe::move(vv), npe::move(tt), npe::move(ff));

npe_end_code()
#include <igl/mesh_with_skeleton.h>

const char* ds_mesh_with_skeleton = R"igl_Qu8mg5v7(

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

 Wrapper using default tetgen_flags
)igl_Qu8mg5v7";

npe_function(mesh_with_skeleton)
npe_doc(ds_mesh_with_skeleton)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(c, Eigen::MatrixXd &)
npe_arg(, Eigen::VectorXi &)
npe_arg(be, Eigen::MatrixXi &)
npe_arg(ce, Eigen::MatrixXi &)
npe_arg(samples_per_bone, int)


npe_begin_code()

  Eigen::MatrixXd & vv;
  Eigen::MatrixXi & tt;
  Eigen::MatrixXi & ff;
  igl::  copyleft::  tetgen::mesh_with_skeleton(v, f, c, , be, ce, samples_per_bone, vv, tt, ff);
  return std::make_tuple(npe::move(vv), npe::move(tt), npe::move(ff));

npe_end_code()


