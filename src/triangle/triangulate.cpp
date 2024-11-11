#include "default_types.h"
#include <igl/triangle/triangulate.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto triangulate(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &E,
    const nb::DRef<const Eigen::MatrixXN> &H,
    const nb::DRef<const Eigen::VectorXI> &VM,
    const nb::DRef<const Eigen::VectorXI> &EM,
    const std::string &flags)
  {
    Eigen::MatrixXN V2;
    Eigen::MatrixXI F2,E2;
    Eigen::VectorXI VM2,EM2;
    igl::triangle::triangulate(V,E,H,VM,EM,flags,V2,F2,VM2,E2,EM2);
    return std::make_tuple(V2,F2,VM2,E2,EM2);
  }
}

// Bind the wrapper to the Python module
void bind_triangulate(nb::module_ &m)
{
  m.def(
    "triangulate",
    &pyigl::triangulate, 
    "V"_a, 
    "E"_a = Eigen::MatrixXI(),
    "H"_a = Eigen::MatrixXN(),
    "VM"_a = Eigen::VectorXI(),
    "EM"_a = Eigen::VectorXI(),
    "flags"_a = "",
R"(Triangulate the interior of a polygon using the triangle library.

@param[in] V #V by 2 list of 2D vertex positions
@param[in] E #E by 2 list of vertex ids forming unoriented edges of the boundary of the polygon
@param[in] H #H by 2 coordinates of points contained inside holes of the polygon
@param[in] VM #V list of markers for input vertices
@param[in] EM #E list of markers for input edges
@param[in] flags  string of options pass to triangle (see triangle documentation)
@param[out] V2  #V2 by 2  coordinates of the vertives of the generated triangulation
@param[out] F2  #F2 by 3  list of indices forming the faces of the generated triangulation
@param[out] VM2  #V2 list of markers for output vertices
@param[out] E2  #E2 by 2 list of output edges
@param[out] EM2  #E2 list of markers for output edges)");
}




