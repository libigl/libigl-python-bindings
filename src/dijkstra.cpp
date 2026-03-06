#include "default_types.h"
#include <igl/dijkstra.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/set.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Dijkstra with uniform edge weights (Euclidean distance via vertex positions)
  auto dijkstra(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const std::vector<std::vector<Integer>> &VV,
    const Integer source,
    const std::set<Integer> &targets)
  {
    Eigen::VectorXN min_distance;
    Eigen::VectorXI previous;
    igl::dijkstra(V, VV, source, targets, min_distance, previous);
    return std::make_tuple(min_distance, previous);
  }
  // Dijkstra with custom vertex weights
  auto dijkstra_weighted(
    const Integer source,
    const std::set<Integer> &targets,
    const std::vector<std::vector<Integer>> &VV,
    const std::vector<double> &weights)
  {
    Eigen::VectorXN min_distance;
    Eigen::VectorXI previous;
    igl::dijkstra(source, targets, VV, weights, min_distance, previous);
    return std::make_tuple(min_distance, previous);
  }
  // Backtrack path from vertex to source
  auto dijkstra_backtrack(
    const Integer vertex,
    const nb::DRef<const Eigen::MatrixXI> &previous)
  {
    // previous[i] single-index access requires IsVectorAtCompileTime — copy to VectorXI
    const Eigen::VectorXI prev = previous.reshaped();
    std::vector<Integer> path;
    igl::dijkstra(vertex, prev, path);
    Eigen::VectorXI result(path.size());
    for (size_t i = 0; i < path.size(); ++i) result(i) = path[i];
    return result;
  }
}

void bind_dijkstra(nb::module_ &m)
{
  m.def("dijkstra", &pyigl::dijkstra,
    "V"_a, "VV"_a, "source"_a, "targets"_a,
    R"(Dijkstra shortest paths using Euclidean edge weights.

@param[in] V  #V by 3 list of vertex positions
@param[in] VV  #V list of adjacency lists (e.g. from adjacency_list)
@param[in] source  source vertex index
@param[in] targets  set of target vertex indices (stop early if reached)
@return min_distance  #V list of minimum distances from source
@return previous  #V list of previous vertex indices for path reconstruction)");

  m.def("dijkstra", &pyigl::dijkstra_weighted,
    "source"_a, "targets"_a, "VV"_a, "weights"_a,
    R"(Dijkstra shortest paths with custom vertex weights.

@param[in] source  source vertex index
@param[in] targets  set of target vertex indices
@param[in] VV  #V list of adjacency lists
@param[in] weights  #V list of vertex weights
@return min_distance  #V list of minimum distances from source
@return previous  #V list of previous vertex indices)");

  m.def("dijkstra_backtrack", &pyigl::dijkstra_backtrack,
    "vertex"_a, "previous"_a,
    R"(Backtrack path from a vertex to the source using Dijkstra's previous array.

@param[in] vertex  destination vertex
@param[in] previous  #V list of previous vertex indices (from dijkstra)
@return path  list of vertex indices from vertex to source)");
}
