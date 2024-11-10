#include "default_types.h"
#include <igl/unique_simplices.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for unique_simplices with overload handling
  auto unique_simplices( const nb::DRef<const Eigen::MatrixXI> &F)
  {
    Eigen::MatrixXI FF;
    Eigen::VectorXI IA,IC;
    igl::unique_simplices(F,FF,IA,IC);
    return nb::make_tuple(FF,IA,IC);
  }
}

// Bind the wrapper to the Python module
void bind_unique_simplices(nb::module_ &m)
{
  m.def(
    "unique_simplices",
    &pyigl::unique_simplices,
    "F"_a,
R"(Find combinatorially unique simplices in F. Order independent.

@param[in] F  #F by simplex-size list of simplices
@param[out] FF  #FF by simplex-size list of unique simplices in F
@param[out] IA (if return_IA=True) #FF index vector so that FF == sort(F(IA,:),2)
@param[out] IC (if return_IC=True) #F index vector so that sort(F,2) == FF(IC,:)
)");
}
