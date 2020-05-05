#include <npe.h>
#include <typedefs.h>






#include <igl/readMSH.h>

const char *ds_read_msh = R"igl_Qu8mg5v7(
Read a mesh (e.g., tet mesh) from a gmsh .msh file

Parameters
----------
filename  path to .msh file
dtype : data-type of the returned vertices, optional. Default is `float64`.
        (returned faces always have type int32.)

Returns
-------

V  #V by 3 list of 3D mesh vertex positions
T  #T by ss list of 3D ss-element indices into V (e.g., ss=4 for tets)

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(read_msh)
npe_doc(ds_read_msh)

npe_arg(filename, std::string)
npe_default_arg(dtypef, npe::dtype, "float")

npe_begin_code()
  if (dtypef.type() == npe::type_f32) {
    EigenDenseF32 v;
    EigenDenseInt t;
    bool ret = igl::readMSH(filename, v, t);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }
    return std::make_tuple(npe::move(v), npe::move(t));
  } else if (dtypef.type() == npe::type_f64) {
    EigenDenseF64 v;
    EigenDenseInt t;
    bool ret = igl::readMSH(filename, v, t);
    if (!ret) {
      throw std::invalid_argument("File '" + filename + "' not found.");
    }
    return std::make_tuple(npe::move(v), npe::move(t));
  } else {
    throw pybind11::type_error("Only float32 and float64 dtypes are supported.");
  }

npe_end_code()


