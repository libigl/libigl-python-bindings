#include "default_types.h"
#include <igl/marching_cubes.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/eigen/sparse.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/unordered_map.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  auto marching_cubes(
    const nb::DRef<const Eigen::VectorXN> &S,
    const nb::DRef<const Eigen::MatrixXN> &GV,
    const unsigned nx,
    const unsigned ny,
    const unsigned nz,
    const Numeric isovalue)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI F;
    std::unordered_map<std::int64_t,int> E2V;
    igl::marching_cubes(S,GV,nx,ny,nz,isovalue,V,F,E2V);
    return std::make_tuple(V,F,E2V);
  }

  auto marching_cubes_sparse(
    const nb::DRef<const Eigen::VectorXN> &S,
    const nb::DRef<const Eigen::MatrixXN> &GV,
    const nb::DRef<const Eigen::MatrixXI> &GI,
    const Numeric isovalue)
  {
    Eigen::MatrixXN V;
    Eigen::MatrixXI F;
    igl::marching_cubes(S,GV,GI,isovalue,V,F);
    return std::make_tuple(V,F);
  }
}

// Bind the wrapper to the Python module
void bind_marching_cubes(nb::module_ &m)
{

  m.def(
    "marching_cubes",
    &pyigl::marching_cubes, 
    "S"_a, 
    "GV"_a,
    "nx"_a,
    "ny"_a,
    "nz"_a,
    "isovalue"_a=0,
R"(Performs marching cubes reconstruction on a grid defined by values, and
points, and generates a mesh defined by vertices and faces

@param[in] S   nx*ny*nz list of values at each grid corner
               i.e. S(x + y*xres + z*xres*yres) for corner (x,y,z)
@param[in] GV  nx*ny*nz by 3 array of corresponding grid corner vertex locations
@param[in] nx  resolutions of the grid in x dimension
@param[in] ny  resolutions of the grid in y dimension
@param[in] nz  resolutions of the grid in z dimension
@param[in] isovalue  the isovalue of the surface to reconstruct
@param[out] V  #V by 3 list of mesh vertex positions
@param[out] F  #F by 3 list of mesh triangle indices into rows of V
@param[out] E2V  map from edge key to index into rows of V

# unpack keys into (i,j,v) index triplets
EV = np.array([[k & 0xFFFFFFFF, k >> 32, v] for k, v in E2V.items()], dtype=np.int64)
)");

  m.def(
    "marching_cubes",
    &pyigl::marching_cubes_sparse, 
    "S"_a, 
    "GV"_a,
    "GI"_a,
    "isovalue"_a=0,
R"(Performs marching cubes reconstruction on a grid defined by values, and
points, and generates a mesh defined by vertices and faces

@param[in] S #S list of scalar field values
@param[in] GV  #S by 3 list of referenced grid vertex positions
@param[in] GI  #GI by 8 list of grid corner indices into rows of GV
@param[in] isovalue  the isovalue of the surface to reconstruct
@param[out] V  #V by 3 list of mesh vertex positions
@param[out] F  #F by 3 list of mesh triangle indices into rows of V)");
}
