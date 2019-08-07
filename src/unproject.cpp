//TODO: __example
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/unproject.h>

const char* ds_unproject = R"igl_Qu8mg5v7(
 Reimplementation of gluUnproject

Parameters
----------
     win  #P by 3 or 3-vector (#P=1) of screen space x, y, and z coordinates
     model  4x4 model-view matrix
     proj  4x4 projection matrix
     viewport  4-long viewport vector

Returns
-------
    scene  #P by 3 or 3-vector (#P=1) the unprojected x, y, and z coordinates

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(unproject)
npe_doc(ds_unproject)

npe_arg(win, dense_float, dense_double)
npe_arg(model, npe_matches(win))
npe_arg(proj, npe_matches(win))
npe_arg(viewport, dense_float, dense_double)


npe_begin_code()

  assert_cols_equals(win, 3, "win");
  assert_rows_equals(model, 4, "model");
  assert_cols_equals(model, 4, "model");
  assert_shapes_match(model, proj, "model", "proj");
  assert_rows_equals(viewport, 4, "viewport");
  npe_Matrix_win scene;
  igl::unproject(win, model, proj, viewport, scene);
  return npe::move(scene);

npe_end_code()
