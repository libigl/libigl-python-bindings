#include "default_types.h"
#include <igl/circumradius.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto circumradius(
    const nb::DRef<const Eigen::MatrixXN> & V ,
    const nb::DRef<const Eigen::MatrixXI> & T)
  {
    Eigen::VectorXN R;
    Eigen::MatrixXN C,B;
    igl::circumradius(V, T, R, C, B);
    return std::make_tuple(R, C, B);
  }
}

void bind_circumradius(nb::module_ &m)
{
  m.def("circumradius", &pyigl::circumradius,
    ""_a,
    "F"_a,
    R"(Compute the circumradius of each triangle in a mesh (V,F)
@param[in] V  #V by dim list of mesh vertex positions
@param[in] F  #F by 3 list of triangle indices into V
@param[out] R  #F list of circumradius
@param[out] R  #T list of circumradius
@param[out] C  #T by dim list of circumcenter
@param[out] B  #T by simplex-size list of barycentric coordinates of circumcenter)");
}
