#include "default_types.h"
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>
#include <igl/copyleft/tetgen/tetrahedralize.h>
#include <Eigen/Core>
#include <string>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Full version with all parameters
  auto tetrahedralize(
    const nb::DRef<const Eigen::MatrixXN>& V,
    const nb::DRef<const Eigen::MatrixXI>& F,
    const nb::DRef<const Eigen::MatrixXN>& H,
    const nb::DRef<const Eigen::VectorXI>& VM,
    const nb::DRef<const Eigen::VectorXI>& FM,
    const nb::DRef<const Eigen::MatrixXN>& R,
    const std::string& flags)
  {
    Eigen::MatrixXN TV;
    Eigen::MatrixXI TT, TF, TN, FT;
    Eigen::VectorXI TM, TR, PT;
    int num_regions = 0;

    int status = igl::copyleft::tetgen::tetrahedralize(V, F, H, VM, FM, R, flags, TV, TT, TF, TM, TR, TN, PT, FT, num_regions);
    if(status != 0)
    {
      // throw error including status code
      throw std::runtime_error("Tetrahedralization failed with status " + std::to_string(status));
    }

    return std::make_tuple(TV, TT, TF, TM, TR, TN, PT, FT, num_regions);
  }
}

void bind_tetrahedralize(nb::module_ &m)
{
  m.def("tetrahedralize", &pyigl::tetrahedralize,
    "V"_a, 
    "F"_a=Eigen::MatrixXI(),
    "H"_a=Eigen::MatrixXN(),
    "VM"_a=Eigen::VectorXI(),
    "FM"_a=Eigen::VectorXI(),
    "R"_a=Eigen::MatrixXN(),
    "flags"_a="",
    R"(Mesh the interior of a surface mesh (V,F) using tetgen

@param[in] V  #V by 3 vertex position list
@param[in] F  #F list of polygon face indices into V (0-indexed)
@param[in] H  #H by 3 list of seed points inside holes
@param[in] VM  #VM list of vertex markers
@param[in] FM  #FM list of face markers
@param[in] R  #R by 5 list of region attributes            
@param[in] flags string of tetgen options (See tetgen documentation) e.g.
    "pq1.414a0.01" tries to mesh the interior of a given surface with
      quality and area constraints
    "" will mesh the convex hull constrained to pass through V (ignores F)
@param[out] TV  #TV by 3 vertex position list
@param[out] TT  #TT by 4 list of tet face indices
@param[out] TF  #TF by 3 list of triangle face indices ('f', else
  `boundary_facets` is called on TT)
@param[out] TR  #TT list of region ID for each tetrahedron      
@param[out] TN  #TT by 4 list of indices neighbors for each tetrahedron ('n')
@param[out] PT  #TV list of incident tetrahedron for a vertex ('m')
@param[out] FT  #TF by 2 list of tetrahedrons sharing a triface ('nn')
@param[out] num_regions Number of regions in output mesh)");

}
