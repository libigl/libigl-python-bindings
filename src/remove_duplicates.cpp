// TODO: __example

#include <common.h>
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
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(epsilon, double)


npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  // remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd nv;
  Eigen::MatrixXi nf;
  Eigen::VectorXi i;
  igl::remove_duplicates(v_copy, f_copy, nv, nf, i, epsilon);
  EigenDenseF64 nv_row_major = nv;
  EigenDenseI64 nf_row_major = nf.template cast<typename EigenDenseI64::Scalar>();
  // FIXME: vector not allowing row major, but they should be essentially the same so i feel we can leave it as col major
  Eigen::Matrix<typename EigenDenseI64::Scalar, Eigen::Dynamic, 1, Eigen::ColMajor> i_row_major = i.template cast<typename EigenDenseI64::Scalar>();
  return std::make_tuple(npe::move(nv_row_major), npe::move(nf_row_major), npe::move(i_row_major));

npe_end_code()


