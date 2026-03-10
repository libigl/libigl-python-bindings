#include "default_types.h"
#include <igl/vector_area_matrix.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto vector_area_matrix(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::SparseMatrix<Numeric> A;
    igl::vector_area_matrix(F, A);
    return A;
  }
}

void bind_vector_area_matrix(nb::module_ &m)
{
  m.def("vector_area_matrix", &pyigl::vector_area_matrix, "F"_a,
    R"(Construct the symmetric vector area matrix A.

[V.col(0)' V.col(1)'] * A * [V.col(0); V.col(1)] is the vector area of mesh (V,F).

@param[in] F  #F by 3 list of triangle indices
@return A  2*#V by 2*#V sparse symmetric area matrix)");
}
