#include <npe.h>
#include <typedefs.h>
#include <igl/peel_winding_number_layers.h>

const char* ds_peel_winding_number_layers = R"igl_Qu8mg5v7(
See peel_winding_number_layers for the documentation.
)igl_Qu8mg5v7";

npe_function(peel_winding_number_layers)
npe_doc(ds_peel_winding_number_layers)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::  copyleft::  cgal::peel_winding_number_layers(v, f, w);
  return npe::move(w);

npe_end_code()


