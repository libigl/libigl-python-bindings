#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <cstdint>

///////////////////////////////////////////////////////////////////////////////////
/// Default numeric and integer types. Passing anything else will result in an
/// implicit copy. Developers insisting on native executation of libigl on
/// single-precision (largely untested and possibly error prone) can change this
/// to float and recompile bindings at their own delight or peril.
///////////////////////////////////////////////////////////////////////////////////
using Numeric = double;
using Integer = int64_t;
using Boolean = bool;
// When using `const nb::DRef<const Eigen::MatrixX*>` this `Options` does not
// affect the input types (either order should result in no copy if `dtype`s
// match). It does affect return types, `Eigen::MatrixXN X; … ; return X;`
constexpr auto Options = Eigen::RowMajor;
namespace Eigen
{
  typedef Matrix<Numeric, Dynamic, Dynamic, Options> MatrixXN;
  typedef Matrix<Integer, Dynamic, Dynamic, Options> MatrixXI;
  typedef Matrix<Boolean, Dynamic, Dynamic, Options> MatrixXB;
  typedef Matrix<Numeric, Dynamic, 1, Eigen::ColMajor> VectorXN;
  typedef Matrix<Integer, Dynamic, 1, Eigen::ColMajor> VectorXI;
  typedef Matrix<Boolean, Dynamic, 1, Eigen::ColMajor> VectorXB;
  typedef Matrix<Numeric, 1, Dynamic, Eigen::RowMajor> RowVectorXN;
  typedef Matrix<Integer, 1, Dynamic, Eigen::RowMajor> RowVectorXI;
  typedef Matrix<Boolean, 1, Dynamic, Eigen::RowMajor> RowVectorXB;
  typedef SparseMatrix<Numeric> SparseMatrixN;
  typedef SparseMatrix<Integer> SparseMatrixI;
  typedef SparseMatrix<Boolean> SparseMatrixB;
}
