#include "default_types.h"
#include <igl/copyleft/cgal/point_areas.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto point_areas(
    const nb::DRef<const Eigen::MatrixXN> &P,
    const nb::DRef<const Eigen::MatrixXI> &I,
    const nb::DRef<const Eigen::MatrixXN> &N)
  {
    Eigen::VectorXN A;
    Eigen::MatrixXN T;
    igl::copyleft::cgal::point_areas(P,I,N,A,T);
    return std::make_tuple(A,T);
  }
}

// Bind the wrapper to the Python module
void bind_point_areas(nb::module_ &m)
{
  m.def(
    "point_areas",
    &pyigl::point_areas,
    "P"_a,
    "I"_a,
    "N"_a,
    R"(Given a 3D set of points P, each with a list of k-nearest-neighbours,
estimate the geodesic voronoi area associated with each point.

The k nearest neighbours may be known from running igl::knn_octree on
the output data from igl::octree. We reccomend using a k value
between 15 and 20 inclusive for accurate area estimation.

N is used filter the neighbours, to ensure area estimation only occurs
using neighbors that are on the same side of the surface (ie for thin
sheets), as well as to solve the orientation ambiguity of the tangent
plane normal.

\note This function *should* be implemented by pre-filtering I, rather
than filtering in this function using N. In this case, the function
would only take P and I as input.

@param[in] P  #P by 3 list of point locations
@param[in] I  #P by k list of k-nearest-neighbor indices into P
@param[in] N  #P by 3 list of point normals
@param[out] A  #P list of estimated areas
@param[out] T  #P by 3 list of tangent plane normals for each point

\see igl::knn)");
}

