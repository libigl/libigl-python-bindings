//TODO: __miss __example
//TODO: mixed use of numeric types

#include <npe.h>
#include <typedefs.h>






#include <igl/unproject_onto_mesh.h>

const char* ds_unproject_onto_mesh = R"igl_Qu8mg5v7(

Unproject a screen location (using current opengl viewport, projection, and
  model view) to a 3D position _onto_ a given mesh, if the ray through the
  given screen location (x,y) _hits_ the mesh.

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
fid  id of the first face hit
bc  barycentric coordinates of hit
Returns true if there's a hit


See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(unproject_onto_mesh)
npe_doc(ds_unproject_onto_mesh)

npe_arg(pos, dense_float, dense_double)
npe_arg(model, npe_matches(pos))
npe_arg(proj, npe_matches(pos))
npe_arg(viewport, npe_matches(pos))
npe_arg(v, npe_matches(pos))
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  // TODO: remove __copy
  Eigen::Vector2f pos_copy = pos.template cast<float>();
  Eigen::Matrix4f model_copy = model.template cast<float>();
  Eigen::Matrix4f proj_copy = proj.template cast<float>();
  Eigen::Vector4f viewport_copy = viewport.template cast<float>();
  int fid;
  npe_Matrix_v bc;
  bool success = igl::unproject_onto_mesh(pos_copy, model_copy, proj_copy, viewport_copy, v, f, fid, bc);
  return std::make_tuple(success, fid, npe::move(bc));

npe_end_code()

