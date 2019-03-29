#include <npe.h>
#include <typedefs.h>
#include <igl/readOFF.h>

const char* ds_read_off = R"igl_Qu8mg5v7(
Read a mesh from an ascii off file, filling in vertex positions, normals
and texture coordinates. Mesh may have faces of any number of degree.

Parameters
----------
filename : string, path to .off file
read_normals : bool, determines whether normals are read. If false, returns []
dtype : data-type of the returned vertices, faces, and normals, optional. Default is `float64`.
        (returned faces always have type int32.)

Returns
-------
v : array of vertex positions #v by 3
f : #f list of face indices into vertex positions
n : list of vertex normals #v by 3

See also
--------
read_triangle_mesh, read_obj

Notes
-----
None

Examples
--------
>>> v, f, n, c = read_off("my_model.off")
)igl_Qu8mg5v7";

npe_function(read_off)
npe_doc(ds_read_off)
npe_arg(filename, std::string)
npe_default_arg(read_normals, bool, true)
npe_default_arg(dtype, npe::dtype, "float64")
npe_begin_code()

  if (dtype.type() == npe::type_f32) {
    EigenDenseF32 v, n;
    EigenDenseI32 f;
    bool ret;
    if (read_normals) {
      ret = igl::readOFF(filename, v, f, n);
    }
    else {
      ret = igl::readOFF(filename, v, f);
    }

    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }

    return std::make_tuple(npe::move(v), npe::move(f), npe::move(n));
  } else if (dtype.type() == npe::type_f64) {
    EigenDenseF64 v, n;
    EigenDenseI32 f;
    bool ret;
    if (read_normals) {
      ret = igl::readOFF(filename, v, f, n);
    }
    else {
      ret = igl::readOFF(filename, v, f);
    }

    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }

    return std::make_tuple(npe::move(v), npe::move(f), npe::move(n));
  } else {
    throw pybind11::type_error("Only float32 and float64 dtypes are supported.");
  }

npe_end_code()
