#include <npe.h>
#include <typedefs.h>
#include <igl/assign.h>

const char* ds_assign = R"igl_Qu8mg5v7(
See assign for the documentation.
)igl_Qu8mg5v7";

npe_function(assign)
npe_doc(ds_assign)

npe_arg(c, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> d;
  igl::  copyleft::  cgal::assign(c, d);
  return npe::move(d);

npe_end_code()
#include <igl/assign.h>

const char* ds_assign = R"igl_Qu8mg5v7(
See assign for the documentation.
)igl_Qu8mg5v7";

npe_function(assign)
npe_doc(ds_assign)

npe_arg(c, dense_float, dense_double)


npe_begin_code()

  igl::  copyleft::  cgal::assign(c);
  return ;

npe_end_code()


