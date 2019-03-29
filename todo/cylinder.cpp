#include <npe.h>
#include <typedefs.h>
#include <igl/cylinder.h>

const char* ds_cylinder = R"igl_Qu8mg5v7(

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

 Construct a triangle mesh of a cylinder (without caps)
  
   Inputs:
     axis_devisions  number of vertices _around the cylinder_
     height_devisions  number of vertices _up the cylinder_
   Outputs:
     V  #V by 3 list of mesh vertex positions
     F  #F by 3 list of triangle indices into V
  
)igl_Qu8mg5v7";

npe_function(cylinder)
npe_doc(ds_cylinder)

npe_arg(axis_devisions, int)
npe_arg(height_devisions, int)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  igl::cylinder(axis_devisions, height_devisions, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()


