#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/bounding_box.h>

const char* ds_bounding_box = R"igl_Qu8mg5v7(

Build a triangle mesh of the bounding box of a given list of vertices

Parameters
----------
V  #V by dim list of rest domain positions

Returns
-------
BV  2^dim by dim list of bounding box corners positions
BF  #BF by dim list of simplex facets 

See also
--------

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(bounding_box)
npe_doc(ds_bounding_box)

npe_arg(v, dense_float, dense_double)


npe_begin_code()

  assert_nonzero_rows(v, "v");
  npe_Matrix_v bv;
  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor, Eigen::Dynamic, Eigen::Dynamic> bf;
  igl::bounding_box(v, bv, bf);
  return std::make_tuple(npe::move(bv), npe::move(bf));

npe_end_code()







const char* ds_bounding_box_pad = R"igl_Qu8mg5v7(
See bounding_box for the documentation.
)igl_Qu8mg5v7";

npe_function(bounding_box)
npe_doc(ds_bounding_box)

npe_arg(v, dense_float, dense_double)
npe_arg(pad, double)


npe_begin_code()

  assert_nonzero_rows(v, "v");
  npe_Matrix_v bv;
  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor, Eigen::Dynamic, Eigen::Dynamic> bf;
  igl::bounding_box(v, pad, bv, bf);
  return std::make_tuple(npe::move(bv), npe::move(bf));

npe_end_code()


