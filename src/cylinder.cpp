// TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/cylinder.h>

const char* ds_cylinder = R"igl_Qu8mg5v7(

Construct a triangle mesh of a cylinder (without caps)

Parameters
----------
axis_devisions  number of vertices _around the cylinder_
height_devisions  number of vertices _up the cylinder_

Returns
-------
V  #V by 3 list of mesh vertex positions
F  #F by 3 list of triangle indices into V

See also
--------


Notes
-----
None

Examples
--------
  
  
)igl_Qu8mg5v7";

npe_function(cylinder)
npe_doc(ds_cylinder)

npe_arg(axis_devisions, int)
npe_arg(height_devisions, int)


npe_begin_code()

  Eigen::MatrixXd v;
  Eigen::MatrixXi f;
  igl::cylinder(axis_devisions, height_devisions, v, f);
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> v_row_major = v;
  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> f_row_major = f;
  return std::make_tuple(npe::move(v_row_major), npe::move(f_row_major));

npe_end_code()


