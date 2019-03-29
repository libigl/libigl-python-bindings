#include <npe.h>
#include <typedefs.h>






#include <igl/remove_duplicates.h>

const char* ds_remove_duplicates = R"igl_Qu8mg5v7(

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

  template <typename T, typename S>
  IGL_INLINE void remove_duplicates(
                                   const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &V,
                                   const Eigen::Matrix<S, Eigen::Dynamic, Eigen::Dynamic> &F,
                                   Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &NV,
                                   Eigen::Matrix<S, Eigen::Dynamic, Eigen::Dynamic> &NF,
                                   Eigen::Matrix<S, Eigen::Dynamic, 1> &I,
                                   const double epsilon = 2.2204e-15);
)igl_Qu8mg5v7";

npe_function(remove_duplicates)
npe_doc(ds_remove_duplicates)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(epsilon, double)


npe_begin_code()

  EigenDense<npe_Scalar_> nv;
  EigenDense<npe_Scalar_> nf;
  Eigen::Matrix<typename DerivedF::Scalar, Eigen::Dynamic, 1> & i;
  igl::remove_duplicates(v, f, epsilon, nv, nf, i);
  return std::make_tuple(npe::move(nv), npe::move(nf), npe::move(i));

npe_end_code()


