#include <npe.h>
#include <typedefs.h>
#include <igl/writeOBJ.h>

const char* ds_write_obj = R"igl_Qu8mg5v7(
Write a mesh in an ascii obj file.

Parameters
----------
filename : path to outputfile
v : array of vertex positions #v by 3
f : #f list of face indices into vertex positions

Returns
-------
ret : bool if output was successful

See also
--------
read_obj

Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> success = write_obj(v, f)
)igl_Qu8mg5v7";

npe_function(write_obj)
npe_doc(ds_write_obj)
npe_arg(filename, std::string)
npe_arg(v, dense_f64, dense_f32)
npe_arg(f, dense_i32, dense_i64)
//npe_default_arg(cn, npe_matches(v), pybind11::array()) TODO: NPE Support none arrays as option
//npe_default_arg(fn, npe_matches(f), pybind11::array())
//npe_default_arg(tc, npe_matches(v), pybind11::array())
//npe_default_arg(ftc, npe_matches(f), pybind11::array())
npe_begin_code()

  //return igl::writeOBJ(filename, v, f, cn, fn, tc, ftc);
  return igl::writeOBJ(filename, v, f);

npe_end_code()




