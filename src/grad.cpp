#include "default_types.h"
#include <igl/grad.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto grad(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    bool uniform = false)
  {
    Eigen::SparseMatrixN G;
    igl::grad(V, F, G, uniform);
    return G;
  }
}

// Bind the wrapper to the Python module
void bind_grad(nb::module_ &m)
{
  m.def(
    "grad",
    &pyigl::grad,
    "V"_a,
    "F"_a,
    "uniform"_a = false,
    R"(Compute the gradient operator on a triangle mesh.
    
    @param[in] V        #V by 3 list of mesh vertex positions
    @param[in] F        #F by 3 (or #F by 4 for tetrahedrons) list of mesh face indices
    @param[out] G       #F*dim by #V Gradient operator
    @param[in] uniform  boolean indicating whether to use a uniform mesh instead of the vertices V
    @return Sparse gradient operator matrix G)"
  );
}
