#include "default_types.h"
#include <igl/project.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for project with batch mode
  auto project(
    const nb::DRef<const Eigen::MatrixXN> &scene,
    const nb::DRef<const Eigen::MatrixXN> &model,
    const nb::DRef<const Eigen::MatrixXN> &proj,
    const nb::DRef<const Eigen::VectorXN> &viewport)
  {
    Eigen::MatrixXN win;
    igl::project(scene, model, proj, viewport, win);
    return win;
  }
}

// Bind the wrapper to the Python module
void bind_project(nb::module_ &m)
{
  m.def(
    "project",
    &pyigl::project,
    "scene"_a,
    "model"_a,
    "proj"_a,
    "viewport"_a,
R"(Eigen reimplementation of gluUnproject for batch processing.

@param[in] scne #P by 3 matrix of screen space x, y, and z coordinates
@param[in] model  4x4 model-view matrix
@param[in] proj  4x4 projection matrix
@param[in] viewport  4-long viewport vector
@return win #P by 3 matrix of the projected x, y, and z coordinates)");

}
