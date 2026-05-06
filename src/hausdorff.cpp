#include "default_types.h"
#include <igl/hausdorff.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto hausdorff(
    const nb::DRef<const Eigen::MatrixXN> &VA,
    const nb::DRef<const Eigen::MatrixXI> &FA,
    const nb::DRef<const Eigen::MatrixXN> &VB,
    const nb::DRef<const Eigen::MatrixXI> &FB)
  {
    Numeric d;
    igl::hausdorff(VA, FA, VB, FB, d);
    return d;
  }
}

void bind_hausdorff(nb::module_ &m)
{
  m.def("hausdorff", &pyigl::hausdorff,
    "VA"_a, "FA"_a, "VB"_a, "FB"_a,
    R"(Compute the Hausdorff distance between two meshes.

d(A,B) = max( max min d(a,b) , max min d(b,a) )
               a∈A b∈B          b∈B a∈A

@param[in] VA  #VA by 3 list of vertex positions of mesh A
@param[in] FA  #FA by 3 list of face indices into VA
@param[in] VB  #VB by 3 list of vertex positions of mesh B
@param[in] FB  #FB by 3 list of face indices into VB
@return d  Hausdorff distance)");
}
