#include <npe.h>
#include <typedefs.h>
#include <igl/read_triangle_mesh.h>

const char* ds_read_triangle_mesh = R"igl_Qu8mg5v7(
Read mesh from an ascii file with automatic detection of file format.
Supported: obj, off, stl, wrl, ply, mesh.

Parameters
----------
filename : string, path to mesh file
dtype : data-type of the returned vertices, optional. Default is `float64`.
        (returned faces always have type int32.)

Returns
-------
v : array of vertex positions #v by 3
f : #f list of face indices into vertex positions

See also
--------
read_obj, read_off, read_stl

Notes
-----
None

Examples
--------
>>> v, f = read_triangle_mesh("my_model.obj")
)igl_Qu8mg5v7";

npe_function(read_triangle_mesh)
npe_doc(ds_read_triangle_mesh)
npe_arg(filename, std::string)
npe_default_arg(dtype, npe::dtype, "float64")
npe_begin_code()

  if (dtype.type() == npe::type_f32) {
    EigenDenseF32 v;
    EigenDenseI32 f;
    bool ret = igl::read_triangle_mesh(filename, v, f);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }
    return std::make_tuple(npe::move(v), npe::move(f));
  } else if (dtype.type() == npe::type_f64) {
    EigenDenseF64 v;
    EigenDenseI32 f;
    bool ret = igl::read_triangle_mesh(filename, v, f);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }
    return std::make_tuple(npe::move(v), npe::move(f));
  } else {
    throw pybind11::type_error("Only float32 and float64 dtypes are supported.");
  }

npe_end_code()

