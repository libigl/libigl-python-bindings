#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>


template <typename LikeT>
using EigenSparseLike = Eigen::SparseMatrix<typename LikeT::Scalar, Eigen::ColMajor>; // FIXME: Maybe we should output CSR if LikeT is row major

template <typename LikeT>
using EigenDenseLike = Eigen::Matrix<typename LikeT::Scalar, Eigen::Dynamic, Eigen::Dynamic, LikeT::Options, Eigen::Dynamic, Eigen::Dynamic>;



const int IglDefaultOptions = Eigen::RowMajor;

template <typename Scalar>
using EigenDense = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic>;

typedef Eigen::Matrix<std::float_t, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> EigenDenseF32;
typedef Eigen::Matrix<std::double_t, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> EigenDenseF64;
typedef Eigen::Matrix<std::int32_t, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> EigenDenseI32;
typedef Eigen::Matrix<std::int64_t, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> EigenDenseI64;

typedef Eigen::SparseMatrix<std::float_t, IglDefaultOptions> EigenSparseF32;
typedef Eigen::SparseMatrix<std::double_t, IglDefaultOptions> EigenSparseF64;
typedef Eigen::SparseMatrix<std::int32_t, IglDefaultOptions> EigenSparseI32;
typedef Eigen::SparseMatrix<std::int64_t, IglDefaultOptions> EigenSparseI64;
