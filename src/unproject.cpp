#include "default_types.h"
#include <igl/unproject.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for unproject with batch mode
  auto unproject(
    const nb::DRef<const Eigen::MatrixXN> &win,
    const nb::DRef<const Eigen::MatrixXN> &model,
    const nb::DRef<const Eigen::MatrixXN> &proj,
    const nb::DRef<const Eigen::VectorXN> &viewport)
  {
    Eigen::MatrixXN scene;
    igl::unproject(win, model, proj, viewport, scene);
    return scene;
  }
}

// Bind the wrapper to the Python module
void bind_unproject(nb::module_ &m)
{
  m.def(
    "unproject",
    &pyigl::unproject,
    "win"_a,
    "model"_a,
    "proj"_a,
    "viewport"_a,
R"(Eigen reimplementation of gluUnproject for batch processing.

@param[in] win  #P by 3 matrix of screen space x, y, and z coordinates
@param[in] model  4x4 model-view matrix
@param[in] proj  4x4 projection matrix
@param[in] viewport  4-long viewport vector
@return scene  #P by 3 matrix of the unprojected x, y, and z coordinates)");

}
