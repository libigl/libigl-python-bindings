#include "default_types.h"
#include <igl/copyleft/cgal/mesh_boolean.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>
#include <string>
#include <tuple>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto mesh_boolean(
    const nb::DRef<const Eigen::MatrixXN> &VA,
    const nb::DRef<const Eigen::MatrixXI> &FA,
    const nb::DRef<const Eigen::MatrixXN> &VB,
    const nb::DRef<const Eigen::MatrixXI> &FB,
    const std::string &type_str)
  {
    Eigen::MatrixXN VC;
    Eigen::MatrixXI FC;
    Eigen::VectorXI J;
    bool success = igl::copyleft::cgal::mesh_boolean(VA, FA, VB, FB, type_str, VC, FC, J);
    if(!success)
    {
      throw std::runtime_error("Mesh boolean failed");
    }
    return std::make_tuple( VC, FC, J);
  }
}

// Bind the wrapper to the Python module
void bind_mesh_boolean(nb::module_ &m)
{
  m.def(
    "mesh_boolean",
    &pyigl::mesh_boolean,
    "VA"_a, 
    "FA"_a, 
    "VB"_a=Eigen::MatrixXN(), 
    "FB"_a=Eigen::MatrixXI(), 
    "type_str"_a,
    R"(Compute the boolean operation (union, intersection, difference, etc.) between two meshes.

@param[in] VA #VA by dim matrix of mesh A vertices
@param[in] FA #FA by simplex_size matrix of mesh A faces
@param[in] VB #VB by dim matrix of mesh B vertices
@param[in] FB #FB by simplex_size matrix of mesh B faces
@param[in] type_str Type of boolean operation: "union", "intersection", "difference", etc.
@param[out] VC #VC by dim matrix of result vertices
@param[out] FC #FC by simplex_size matrix of result faces
@param[out] J #FC list of indices indicating which input face contributed to each result face
@return Tuple containing:
  - VC: Result vertices
  - FC: Result faces
  - J: Face origin indices)");
}
