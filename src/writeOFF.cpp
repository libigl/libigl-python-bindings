#include <common.h>
#include <npe.h>
#include <typedefs.h>

// TODO None arguments


#include <igl/writeOFF.h>

const char* ds_write_off = R"igl_Qu8mg5v7(
Export geometry and colors-by-vertex
   Export a mesh from an ascii OFF file, filling in vertex positions.
   Only triangle meshes are supported

Parameters
----------
    str  path to .off output file
     V  #V by 3 mesh vertex positions
     F  #F by 3 mesh indices into V
     C  double matrix of rgb values per vertex #V by 3


Returns
-------
    Returns true on success, false on errors

See also
--------


Notes
-----
None

Examples
--------
   
)igl_Qu8mg5v7";

npe_function(write_off)
npe_doc(ds_write_off)

npe_arg(str, std::string)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(c, npe_matches(v))


npe_begin_code()

  assert_valid_3d_tri_mesh(v, f);
  return igl::writeOFF(str, v, f, c);

npe_end_code()
// #include <igl/writeOFF.h>

// const char* ds_write_off = R"igl_Qu8mg5v7(
// See writeOFF for the documentation.
// )igl_Qu8mg5v7";

// npe_function(write_off)
// npe_doc(ds_write_off)

// npe_arg(str, std::string)
// npe_arg(v, dense_float, dense_double)
// npe_arg(f, dense_int, dense_long, dense_longlong)


// npe_begin_code()

//   igl::writeOFF(str, v, f);
//   return ;

// npe_end_code()


