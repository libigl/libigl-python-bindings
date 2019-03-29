#include <npe.h>
#include <typedefs.h>






#include <igl/unproject_onto_mesh.h>

const char* ds_unproject_onto_mesh = R"igl_Qu8mg5v7(

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

 Unproject a screen location (using current opengl viewport, projection, and
   model view) to a 3D position _onto_ a given mesh, if the ray through the
   given screen location (x,y) _hits_ the mesh.
  
   Inputs:
      pos        screen space coordinates
      model      model matrix
      proj       projection matrix
      viewport   vieweport vector
      V   #V by 3 list of mesh vertex positions
      F   #F by 3 list of mesh triangle indices into V
   Outputs:
      fid  id of the first face hit
      bc  barycentric coordinates of hit
   Returns true if there's a hit
)igl_Qu8mg5v7";

npe_function(unproject_onto_mesh)
npe_doc(ds_unproject_onto_mesh)

npe_arg(pos, Eigen::Vector2f &)
npe_arg(model, Eigen::Matrix4f &)
npe_arg(proj, Eigen::Matrix4f &)
npe_arg(viewport, Eigen::Vector4f &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  int & fid;
  EigenDense<npe_Scalar_> bc;
  igl::unproject_onto_mesh(pos, model, proj, viewport, v, f, fid, bc);
  return std::make_tuple(npe::move(fid), npe::move(bc));

npe_end_code()
#include <igl/unproject_onto_mesh.h>

const char* ds_unproject_onto_mesh = R"igl_Qu8mg5v7(

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
      pos        screen space coordinates
      model      model matrix
      proj       projection matrix
      viewport   vieweport vector
      shoot_ray  function handle that outputs hits of a given ray against a
        mesh (embedded in function handles as captured variable/data)
   Outputs:
      fid  id of the first face hit
      bc  barycentric coordinates of hit
   Returns true if there's a hit
)igl_Qu8mg5v7";

npe_function(unproject_onto_mesh)
npe_doc(ds_unproject_onto_mesh)

npe_arg(pos, Eigen::Vector2f &)
npe_arg(model, Eigen::Matrix4f &)
npe_arg(proj, Eigen::Matrix4f &)
npe_arg(viewport, Eigen::Vector4f &)
npe_arg(shoot_ray, std::function<bool (const Eigen::Vector3f &, const Eigen::Vector3f &, igl::Hit &)> &)


npe_begin_code()

  int & fid;
  EigenDense<npe_Scalar_> bc;
  igl::unproject_onto_mesh(pos, model, proj, viewport, shoot_ray, fid, bc);
  return std::make_tuple(npe::move(fid), npe::move(bc));

npe_end_code()


