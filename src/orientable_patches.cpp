#include "default_types.h"
#include <igl/orientable_patches.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Simple overload: just return component ids
  auto orientable_patches(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXI C;
    igl::orientable_patches(F, C);
    return C;
  }
  // With adjacency matrix
  auto orientable_patches_with_adj(const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::VectorXI C;
    Eigen::SparseMatrix<Numeric> A;
    igl::orientable_patches(F, C, A);
    return std::make_tuple(C, A);
  }
}

void bind_orientable_patches(nb::module_ &m)
{
  m.def("orientable_patches", &pyigl::orientable_patches, "F"_a,
    R"(Compute connected components of facets connected by manifold edges.

@param[in] F  #F by simplex_size list of facets
@return C  #F list of component ids)");

  m.def("orientable_patches", &pyigl::orientable_patches_with_adj, "F"_a,
    R"(Compute connected components of facets connected by manifold edges,
also returns the adjacency matrix.

@param[in] F  #F by simplex_size list of facets
@return C  #F list of component ids
@return A  #F by #F sparse adjacency matrix)");
}
