#include <npe.h>
#include <typedefs.h>






#include <igl/read_triangle_mesh.h>

const char* ds_read_triangle_mesh = R"igl_Qu8mg5v7(

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

 Simple wrapper, reads floating point precision but assigns to
       DerivedV::Scalar which may be a CGAL type
      
       Inputs:
         str  path to file
       Outputs:
         V  eigen double matrix #V by 3
         F  eigen int matrix #F by 3
       Returns true iff success
)igl_Qu8mg5v7";

npe_function(read_triangle_mesh)
npe_doc(ds_read_triangle_mesh)

npe_arg(str, std::string)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  igl::  copyleft::  cgal::read_triangle_mesh(str, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()


