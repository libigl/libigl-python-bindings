#include "default_types.h"
#include <igl/all_pairs_distances.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto all_pairs_distances(
      const Eigen::MatrixXd &V,
      const Eigen::MatrixXd &U,
      const bool squared)
  {
    Eigen::MatrixXd D;
    igl::all_pairs_distances(V, U, squared, D);
    return D;
  }
}

void bind_all_pairs_distances(nb::module_ &m)
{
  m.def("all_pairs_distances", &pyigl::all_pairs_distances,
        "V"_a,
        "U"_a,
        "squared"_a,
        R"(Compute distances between each point i in V and point j in U
    D = all_pairs_distances(V,U)
@tparam matrix class like MatrixXd
@param[in] V  #V by dim list of points
@param[in] U  #U by dim list of points
@param[in] squared  whether to return squared distances
@param[out] D  #V by #U matrix of distances, where D(i,j) gives the distance or
    squareed distance between V(i,:) and U(j,:)
)");
}
