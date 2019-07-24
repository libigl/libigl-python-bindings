// TODO: __example

#include <npe.h>
#include <typedefs.h>






#include <igl/remove_duplicates.h>


const char* ds_remove_duplicates = R"igl_Qu8mg5v7(

Merge the duplicate vertices from V, fixing the topology accordingly

Parameters
----------
V,F       mesh description
epsilon   minimal distance to consider two vertices identical

Returns
-------
NV, NF    new mesh without duplicate vertices

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(remove_duplicates)
npe_doc(ds_remove_duplicates)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(epsilon, double)


npe_begin_code()

  // remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd nv;
  Eigen::MatrixXi nf;
  Eigen::VectorXi i;
  igl::remove_duplicates(v_copy, f_copy, nv, nf, i, epsilon);
  return std::make_tuple(npe::move(nv), npe::move(nf), npe::move(i));

npe_end_code()


