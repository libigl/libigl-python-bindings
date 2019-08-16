#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>


const int IglDefaultOptions = Eigen::RowMajor;

constexpr bool opts_dontalign(int options) {
    return (options == (Eigen::ColMajor | Eigen::DontAlign) || options == (Eigen::RowMajor | Eigen::DontAlign));
}

template <bool DontAlign, int Opts>
struct OptExtractor {
    enum {
        Options = Opts
    };
};

template <int Opts>
struct OptExtractor<true, Opts> {
    enum Options {
        Options = Eigen::RowMajor
    };
};

template <typename LikeT>
using EigenSparseLike = Eigen::SparseMatrix<typename LikeT::Scalar, Eigen::ColMajor>; // FIXME: Maybe we should output CSR if LikeT is row major

template <typename LikeT>
using EigenDenseLike = Eigen::Matrix<typename LikeT::Scalar, Eigen::Dynamic, Eigen::Dynamic, OptExtractor<opts_dontalign(LikeT::Options), LikeT::Options>::Options, Eigen::Dynamic, Eigen::Dynamic>;

template <typename Scalar>
using EigenDense = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic>;

typedef Eigen::Matrix<std::float_t, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> EigenDenseF32;
typedef Eigen::Matrix<std::double_t, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> EigenDenseF64;
typedef Eigen::Matrix<std::int32_t, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> EigenDenseI32;
typedef Eigen::Matrix<std::int64_t, Eigen::Dynamic, Eigen::Dynamic, IglDefaultOptions, Eigen::Dynamic, Eigen::Dynamic> EigenDenseI64;

//TODO replace with fancy CMAKE
#ifdef WIN32
typedef EigenDenseF64 EigenDenseFloat;
typedef EigenDenseI32 EigenDenseInt;
#else
typedef EigenDenseF64 EigenDenseFloat;
typedef EigenDenseI64 EigenDenseInt;
#endif

typedef Eigen::SparseMatrix<std::float_t, IglDefaultOptions> EigenSparseF32;
typedef Eigen::SparseMatrix<std::double_t, IglDefaultOptions> EigenSparseF64;
typedef Eigen::SparseMatrix<std::int32_t, IglDefaultOptions> EigenSparseI32;
typedef Eigen::SparseMatrix<std::int64_t, IglDefaultOptions> EigenSparseI64;
