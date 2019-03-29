#include <npe.h>
#include <typedefs.h>
#include <igl/is_edge_manifold.h>

const char* ds_is_edge_manifold = R"igl_Qu8mg5v7(

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

 check if the mesh is edge-manifold
  
   Inputs:
     V  #V by dim list of mesh vertex positions **unneeded**
     F  #F by 3 list of triangle indices
   Returns whether mesh is edge manifold.
  
   Known Bugs:
    Does not check for non-manifold vertices
  
   See also: is_vertex_manifold
)igl_Qu8mg5v7";

npe_function(is_edge_manifold)
npe_doc(ds_is_edge_manifold)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> bf;
  EigenDense<npe_Scalar_> e;
  EigenDense<npe_Scalar_> emap;
  EigenDense<npe_Scalar_> be;
  igl::is_edge_manifold(f, bf, e, emap, be);
  return std::make_tuple(npe::move(bf), npe::move(e), npe::move(emap), npe::move(be));

npe_end_code()
#include <igl/is_edge_manifold.h>

const char* ds_is_edge_manifold = R"igl_Qu8mg5v7(
See is_edge_manifold for the documentation.
)igl_Qu8mg5v7";

npe_function(is_edge_manifold)
npe_doc(ds_is_edge_manifold)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  igl::is_edge_manifold(f);
  return ;

npe_end_code()


