#include <npe.h>
#include <typedefs.h>
#include <igl/resolve_intersections.h>

const char* ds_resolve_intersections = R"igl_Qu8mg5v7(
See resolve_intersections for the documentation.
)igl_Qu8mg5v7";

npe_function(resolve_intersections)
npe_doc(ds_resolve_intersections)

npe_arg(v, dense_float, dense_double)
npe_arg(e, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> vi;
  EigenDense<npe_Scalar_> ei;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> im;
  igl::  copyleft::  cgal::resolve_intersections(v, e, vi, ei, j, im);
  return std::make_tuple(npe::move(vi), npe::move(ei), npe::move(j), npe::move(im));

npe_end_code()


