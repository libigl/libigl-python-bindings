#include "default_types.h"
#include <igl/copyleft/marching_cubes.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto marching_cubes(
    const nb::DRef<const Eigen::VectorXN> &values,
    const nb::DRef<const Eigen::MatrixXN> &points,
    const Integer x_res,
    const Integer y_res,
    const Integer z_res,
    const Numeric isovalue)
  {
    Eigen::MatrixXN vertices;
    Eigen::MatrixXI faces;
    igl::copyleft::marching_cubes(
      values, points,
      (unsigned)x_res, (unsigned)y_res, (unsigned)z_res,
      isovalue, vertices, faces);
    return std::make_tuple(vertices, faces);
  }
  auto marching_cubes_indexed(
    const nb::DRef<const Eigen::VectorXN> &values,
    const nb::DRef<const Eigen::MatrixXN> &points,
    const nb::DRef<const Eigen::MatrixXI> &indices,
    const Numeric isovalue)
  {
    Eigen::MatrixXN vertices;
    Eigen::MatrixXI faces;
    igl::copyleft::marching_cubes(values, points, indices, isovalue, vertices, faces);
    return std::make_tuple(vertices, faces);
  }
}

void bind_marching_cubes(nb::module_ &m)
{
  m.def("marching_cubes", &pyigl::marching_cubes,
    "values"_a, "points"_a, "x_res"_a, "y_res"_a, "z_res"_a, "isovalue"_a = 0.0,
    R"(Perform marching cubes to extract an isosurface from a scalar field on a regular grid.

@param[in] values  #points vector of scalar values (<0 inside, >0 outside)
@param[in] points  #points by 3 grid point positions (x-fastest order:
    index = x + y*x_res + z*x_res*y_res)
@param[in] x_res  grid resolution in x
@param[in] y_res  grid resolution in y
@param[in] z_res  grid resolution in z
@param[in] isovalue  isovalue to reconstruct (default: 0.0)
@return tuple (vertices, faces):
  - vertices  #V by 3 mesh vertex positions
  - faces  #F by 3 mesh triangle indices)");
  m.def("marching_cubes", &pyigl::marching_cubes_indexed,
    "values"_a, "points"_a, "indices"_a, "isovalue"_a = 0.0,
    R"(Perform marching cubes on a sparse grid defined by explicit cube corner indices.

@param[in] values  #points vector of scalar values
@param[in] points  #points by 3 grid point positions
@param[in] indices  #cubes by 8 array of corner indices into points/values
@param[in] isovalue  isovalue to reconstruct (default: 0.0)
@return tuple (vertices, faces):
  - vertices  #V by 3 mesh vertex positions
  - faces  #F by 3 mesh triangle indices)");
}
