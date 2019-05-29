#include <npe.h>
#include <typedefs.h>
#include <igl/sort_triangles.h>

const char* ds_sort_triangles = R"igl_Qu8mg5v7(
See sort_triangles for the documentation.
)igl_Qu8mg5v7";

npe_function(sort_triangles)
npe_doc(ds_sort_triangles)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> i;
  igl::  opengl2::sort_triangles(v, f, ff, i);
  return std::make_tuple(npe::move(ff), npe::move(i));

npe_end_code()
#include <igl/sort_triangles_slow.h>

const char* ds_sort_triangles_slow = R"igl_Qu8mg5v7(
See sort_triangles_slow for the documentation.
)igl_Qu8mg5v7";

npe_function(sort_triangles_slow)
npe_doc(ds_sort_triangles_slow)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> i;
  igl::  opengl2::sort_triangles_slow(v, f, ff, i);
  return std::make_tuple(npe::move(ff), npe::move(i));

npe_end_code()


