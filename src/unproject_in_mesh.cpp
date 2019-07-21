#include <npe.h>
#include <typedefs.h>






#include <igl/unproject_in_mesh.h>

const char* ds_unproject_in_mesh = R"igl_Qu8mg5v7(

Unproject a screen location (using current opengl viewport, projection, and
   model view) to a 3D position _inside_ a given mesh. If the ray through the
   given screen location (x,y) _hits_ the mesh more than twice then the 3D
   midpoint between the first two hits is return. If it hits once, then that
   point is return. If it does not hit the mesh then obj is not set.

Parameters
----------
pos        screen space coordinates
model      model matrix
proj       projection matrix
viewport   vieweport vector
V   #V by 3 list of mesh vertex positions
F   #F by 3 list of mesh triangle indices into V

Returns
-------
obj        3d unprojected mouse point in mesh
hits       vector of hits
Returns number of hits


See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(unproject_in_mesh)
npe_doc(ds_unproject_in_mesh)

npe_arg(pos, Eigen::Vector2f &)
npe_arg(model, Eigen::Matrix4f &)
npe_arg(proj, Eigen::Matrix4f &)
npe_arg(viewport, Eigen::Vector4f &)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()


  // TODO: remove __copy
  Eigen::Vector2f pos_copy = pos.template cast<float>();
  Eigen::Matrix4f model_copy = model.template cast<float>();
  Eigen::Matrix4f proj_copy = proj.template cast<float>();
  Eigen::Vector4f viewport_copy = viewport.template cast<float>();

  npe_Matrix_v obj;
  std::vector<igl::Hit, std::allocator<igl::Hit> > hits;
  igl::unproject_in_mesh(pos, model, proj, viewport, v, f, obj, hits);
  return std::make_tuple(npe::move(obj), hits);

npe_end_code()

