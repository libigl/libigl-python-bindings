//TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>


#include <igl/write_triangle_mesh.h>

const char *ds_write_triangle_mesh = R"igl_Qu8mg5v7(
 write mesh to a file with automatic detection of file format.  supported: obj, off, stl, wrl, ply, mesh).

Parameters
----------
    str  path to file
     V  eigen double matrix #V by 3
     F  eigen int matrix #F by 3
    force_ascii=True  force ascii format even if binary is available
Returns
-------
    Returns true iff success

See also
--------


Notes
-----


Examples
--------

)igl_Qu8mg5v7";

npe_function(write_triangle_mesh)
npe_doc(ds_write_triangle_mesh)

npe_arg(str, std::string)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_default_arg(force_ascii, bool, bool(true))



npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  // TODO: remove __copy
  //copy is necessary for the ply library
  Eigen::MatrixXi f_copy = f.template cast<int>();
  bool ok = igl::write_triangle_mesh(str, v, f_copy, force_ascii);
  return ok;

npe_end_code()


