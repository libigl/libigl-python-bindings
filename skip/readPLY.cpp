#include <npe.h>
#include <typedefs.h>






#include <igl/readPLY.h>

const char* ds_read_ply = R"igl_Qu8mg5v7(

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

 Read a mesh from a .ply file. 
  
   Inputs:
     filename  path to .ply file
   Outputs:
     V  #V by 3 list of vertex positions
     F  #F list of lists of triangle indices
     N  #V by 3 list of vertex normals
     UV  #V by 2 list of vertex texture coordinates
   Returns true iff success
)igl_Qu8mg5v7";

npe_function(read_ply)
npe_doc(ds_read_ply)

npe_arg(filename, std::string)


npe_begin_code()

  std::vector<std::vector<Vtype> > & v;
  std::vector<std::vector<Ftype> > & f;
  std::vector<std::vector<Ntype> > & n;
  std::vector<std::vector<UVtype> > & uv;
  igl::readPLY(filename, v, f, n, uv);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(n), npe::move(uv));

npe_end_code()
#include <igl/readPLY.h>

const char* ds_read_ply = R"igl_Qu8mg5v7(
See readPLY for the documentation.
)igl_Qu8mg5v7";

npe_function(read_ply)
npe_doc(ds_read_ply)



npe_begin_code()

  FILE * ply_file;
  std::vector<std::vector<Vtype> > & v;
  std::vector<std::vector<Ftype> > & f;
  std::vector<std::vector<Ntype> > & n;
  std::vector<std::vector<UVtype> > & uv;
  igl::readPLY(ply_file, v, f, n, uv);
  return std::make_tuple(npe::move(ply_file), npe::move(v), npe::move(f), npe::move(n), npe::move(uv));

npe_end_code()
#include <igl/readPLY.h>

const char* ds_read_ply = R"igl_Qu8mg5v7(
See readPLY for the documentation.
)igl_Qu8mg5v7";

npe_function(read_ply)
npe_doc(ds_read_ply)

npe_arg(filename, std::string)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  EigenDense<npe_Scalar_> n;
  EigenDense<npe_Scalar_> uv;
  igl::readPLY(filename, v, f, n, uv);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(n), npe::move(uv));

npe_end_code()
#include <igl/readPLY.h>

const char* ds_read_ply = R"igl_Qu8mg5v7(
See readPLY for the documentation.
)igl_Qu8mg5v7";

npe_function(read_ply)
npe_doc(ds_read_ply)

npe_arg(filename, std::string)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  igl::readPLY(filename, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()


