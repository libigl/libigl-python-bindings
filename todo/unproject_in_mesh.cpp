#include <npe.h>
#include <typedefs.h>






#include <igl/unproject_in_mesh.h>

const char* ds_unproject_in_mesh = R"igl_Qu8mg5v7(

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
   model view) to a 3D position _inside_ a given mesh. If the ray through the
   given screen location (x,y) _hits_ the mesh more than twice then the 3D
   midpoint between the first two hits is return. If it hits once, then that
   point is return. If it does not hit the mesh then obj is not set.
  
   Inputs:
      pos        screen space coordinates
      model      model matrix
      proj       projection matrix
      viewport   vieweport vector
      V   #V by 3 list of mesh vertex positions
      F   #F by 3 list of mesh triangle indices into V
   Outputs:
      obj        3d unprojected mouse point in mesh
      hits       vector of hits
   Returns number of hits
  
)igl_Qu8mg5v7";

npe_function(unproject_in_mesh)
npe_doc(ds_unproject_in_mesh)

npe_arg(pos, Eigen::Vector2f &)
npe_arg(model, Eigen::Matrix4f &)
npe_arg(proj, Eigen::Matrix4f &)
npe_arg(viewport, Eigen::Vector4f &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> obj;
  std::vector<igl::Hit> & hits;
  igl::unproject_in_mesh(pos, model, proj, viewport, v, f, obj, hits);
  return std::make_tuple(npe::move(obj), npe::move(hits));

npe_end_code()
#include <igl/unproject_in_mesh.h>

const char* ds_unproject_in_mesh = R"igl_Qu8mg5v7(

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
      shoot_ray  function handle that outputs first hit of a given ray
        against a mesh (embedded in function handles as captured
        variable/data)
   Outputs:
      obj        3d unprojected mouse point in mesh
      hits       vector of hits
   Returns number of hits
  
)igl_Qu8mg5v7";

npe_function(unproject_in_mesh)
npe_doc(ds_unproject_in_mesh)

npe_arg(pos, Eigen::Vector2f &)
npe_arg(model, Eigen::Matrix4f &)
npe_arg(proj, Eigen::Matrix4f &)
npe_arg(viewport, Eigen::Vector4f &)
npe_arg(shoot_ray, std::function<void (const Eigen::Vector3f &, const Eigen::Vector3f &, std::vector<igl::Hit> &)> &)


npe_begin_code()

  EigenDense<npe_Scalar_> obj;
  std::vector<igl::Hit> & hits;
  igl::unproject_in_mesh(pos, model, proj, viewport, shoot_ray, obj, hits);
  return std::make_tuple(npe::move(obj), npe::move(hits));

npe_end_code()
#include <igl/unproject_in_mesh.h>

const char* ds_unproject_in_mesh = R"igl_Qu8mg5v7(
See unproject_in_mesh for the documentation.
)igl_Qu8mg5v7";

npe_function(unproject_in_mesh)
npe_doc(ds_unproject_in_mesh)

npe_arg(pos, Eigen::Vector2f &)
npe_arg(model, Eigen::Matrix4f &)
npe_arg(proj, Eigen::Matrix4f &)
npe_arg(viewport, Eigen::Vector4f &)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> obj;
  igl::unproject_in_mesh(pos, model, proj, viewport, v, f, obj);
  return npe::move(obj);

npe_end_code()


