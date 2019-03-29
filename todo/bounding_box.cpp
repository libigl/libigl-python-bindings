#include <npe.h>
#include <typedefs.h>
#include <igl/bounding_box.h>

const char* ds_bounding_box = R"igl_Qu8mg5v7(

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

 Build a triangle mesh of the bounding box of a given list of vertices
   
   Inputs:
     V  #V by dim list of rest domain positions
   Outputs:
     BV  2^dim by dim list of bounding box corners positions
     BF  #BF by dim list of simplex facets 
)igl_Qu8mg5v7";

npe_function(bounding_box)
npe_doc(ds_bounding_box)

npe_arg(v, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> bv;
  EigenDense<npe_Scalar_> bf;
  igl::bounding_box(v, bv, bf);
  return std::make_tuple(npe::move(bv), npe::move(bf));

npe_end_code()






#include <igl/bounding_box.h>

const char* ds_bounding_box = R"igl_Qu8mg5v7(
See bounding_box for the documentation.
)igl_Qu8mg5v7";

npe_function(bounding_box)
npe_doc(ds_bounding_box)

npe_arg(v, dense_f32, dense_f64)
npe_arg(pad, typename DerivedV::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> bv;
  EigenDense<npe_Scalar_> bf;
  igl::bounding_box(v, pad, bv, bf);
  return std::make_tuple(npe::move(bv), npe::move(bf));

npe_end_code()


