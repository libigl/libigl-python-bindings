#include "default_types.h"
#include <igl/edge_flaps.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <tuple>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Binding for the first overload of edge_flaps with `uE` and `EMAP` as inputs
  auto edge_flaps(
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::MatrixXI> &uE,
    const nb::DRef<const Eigen::VectorXI> &EMAP)
  {
    Eigen::MatrixXI EF, EI;
    igl::edge_flaps(F, uE, EMAP, EF, EI);
    return std::make_tuple(EF, EI);
  }

  // Binding for the second overload of edge_flaps where `uE` and `EMAP` are outputs
  auto edge_flaps_F(
    const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI uE, EF, EI;
    Eigen::VectorXI EMAP;
    igl::edge_flaps(F, uE, EMAP, EF, EI);
    return std::make_tuple(uE, EMAP, EF, EI);
  }
}

// Bind the wrapper to the Python module
void bind_edge_flaps(nb::module_ &m)
{
  m.def(
    "edge_flaps",
    &pyigl::edge_flaps,
    "F"_a,
    "uE"_a,
    "EMAP"_a,
    R"(Determine edge flaps with precomputed unique edge map and edge-face adjacency.

    @param[in] F  #F by 3 list of face indices
    @param[in] uE  #uE by 2 list of unique edge indices
    @param[in] EMAP #F*3 list of indices mapping each directed edge to unique edge in uE
    @return Tuple containing EF and EI matrices, where:
            EF - #E by 2 list of edge flaps
            EI - #E by 2 list of edge flap corners)");

  m.def(
    "edge_flaps",
    &pyigl::edge_flaps_F,
    "F"_a,
    R"(Determine edge flaps, unique edge map, and edge-face adjacency from face list only.

    @param[in] F  #F by 3 list of face indices
    @return Tuple containing uE, EMAP, EF, and EI where:
            uE - #uE by 2 list of unique edge indices
            EMAP - #F*3 list mapping each directed edge to unique edge in uE
            EF - #E by 2 list of edge flaps
            EI - #E by 2 list of edge flap corners)");
}
