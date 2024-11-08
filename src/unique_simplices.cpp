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
  nb::object unique_simplices(
    const nb::DRef<const Eigen::MatrixXI> &F,
    const bool return_IA,
    const bool return_IC)
  {
    Eigen::MatrixXI FF;
    Eigen::VectorXI IA,IC;
    igl::unique_simplices(F,FF,IA,IC);
    if(return_IA && return_IC)
    {
      return nb::make_tuple(FF,IA,IC);
    }else if(return_IA)
    {
      return nb::make_tuple(FF,IA);
    }else if(return_IC)
    {
      return nb::make_tuple(FF,IC);
    }
    return nb::cast(std::move(FF));
  }
}

// Bind the wrapper to the Python module
void bind_unique_simplices(nb::module_ &m)
{
  m.def(
    "unique_simplices",
    &pyigl::unique_simplices,
    "F"_a,
    "return_IA"_a = false,
    "return_IC"_a = false,
R"(Find combinatorially unique simplices in F. Order independent.

@param[in] F  #F by simplex-size list of simplices
@param[out] FF  #FF by simplex-size list of unique simplices in F
@param[out] IA (if return_IA=True) #FF index vector so that FF == sort(F(IA,:),2)
@param[out] IC (if return_IC=True) #F index vector so that sort(F,2) == FF(IC,:)
)");
}
