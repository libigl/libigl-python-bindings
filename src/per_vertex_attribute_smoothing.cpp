// TODO: __example

#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/per_vertex_attribute_smoothing.h>

const char* ds_per_vertex_attribute_smoothing = R"igl_Qu8mg5v7(

Smooth vertex attributes using uniform Laplacian

Parameters
----------
Ain  #V by #A eigen Matrix of mesh vertex attributes (each vertex has #A attributes)
F    #F by 3 eigne Matrix of face (triangle) indices

Returns
-------
Aout #V by #A eigen Matrix of mesh vertex attributes

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(per_vertex_attribute_smoothing)
npe_doc(ds_per_vertex_attribute_smoothing)

npe_arg(ain, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_3d_tri_mesh(ain, f);
  // remove __copy
  Eigen::MatrixXd ain_copy = ain.template cast<double>();
  Eigen::MatrixXd aout;
  igl::per_vertex_attribute_smoothing(ain_copy, f, aout);
  return npe::move(aout);

npe_end_code()


