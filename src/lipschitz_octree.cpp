#include "default_types.h"
#include <igl/lipschitz_octree.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/function.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Hopefully this will avoid a copy by matching the type in lipschitz_octree_prune
  using MatrixNX3R = Eigen::Matrix<Numeric, Eigen::Dynamic, 3, Eigen::RowMajor>;
  auto lipschitz_octree(
    const nb::DRef<const Eigen::VectorXN> &origin,
    const Numeric h0,
    const Integer max_depth,
    const nb::typed<
      nb::callable,
      Eigen::VectorXN(const nb::DRef<const MatrixNX3R> &)> & udf)
  {
    Eigen::MatrixXI ijk;
    // Instead of MatrixXN if use use MatrixNX3R we might avoid a copy
    const std::function<Eigen::VectorXN(const MatrixNX3R &)> udf_wrapper =
      [&](const MatrixNX3R &Q) -> Eigen::VectorXN
    {
      return nb::cast<Eigen::VectorXN>(udf(Q));
    };
    igl::lipschitz_octree<true>(origin, h0, max_depth, udf_wrapper, ijk);
    return ijk;
  }
}

// Bind the wrapper to the Python module
void bind_lipschitz_octree(nb::module_ &m)
{
  m.def(
    "lipschitz_octree",
    &pyigl::lipschitz_octree, 
    "origin"_a, 
    "h0"_a,
    "max_depth"_a,
    "udf"_a,
R"(Given a minimum corner position (origin) and a side length (h0) and a
maximum depth (max_depth), determine the possible active leaf octree cells
based on an one-Lipschitz non-negative function to a level set (e.g.,
"unsigned distance function").

  @param[in] origin  3-vector of root cell origin (minimum corner)
  @param[in] h0   side length of root cell
  @param[in] max_depth  maximum depth of octree (root is depth=0)
  @param[in] udf  1-Lipschitz function of (unsigned) distance to level set to a
    list of batched query points
  @param[out] ijk #ijk by 3 list of octree leaf cell minimum corner
    subscripts
)");
}



