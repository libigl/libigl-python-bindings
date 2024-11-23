#include "default_types.h"
#include <igl/cylinder.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto cylinder(
    int axis_devisions,
    int height_devisions)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI F;
    igl::cylinder(axis_devisions, height_devisions, V, F);
    return std::make_tuple(V, F);
  }
}

void bind_cylinder(nb::module_ &m)
{
  m.def("cylinder", &pyigl::cylinder,
    "axis_devisions"_a,
    "height_devisions"_a,
    R"(Construct a triangle mesh of a cylinder (without caps)
@param[in] axis_devisions  number of vertices _around the cylinder_
@param[in] height_devisions  number of vertices _up the cylinder_
@param[out] V  #V by 3 list of mesh vertex positions
@param[out] F  #F by 3 list of triangle indices into V)");
}
