#include "default_types.h"
#include <igl/biharmonic_coordinates.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace nb::literals;
namespace pyigl
{
  auto biharmonic_coordinates(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &T,
    const std::vector<std::vector<Integer>> &S,
    const int k)
  {
    Eigen::MatrixXN W;
    igl::biharmonic_coordinates(V, T, S, k, W);
    return W;
  }
}

void bind_biharmonic_coordinates(nb::module_ &m)
{
  m.def("biharmonic_coordinates", &pyigl::biharmonic_coordinates,
    "V"_a,
    "T"_a,
    "S"_a,
    "k"_a=2,
    R"(Compute "discrete biharmonic generalized barycentric coordinates" as
described in "Linear Subspace Design for Real-Time Shape Deformation"
[Wang et al. 2015]. Not to be confused with "Bounded Biharmonic Weights
for Real-Time Deformation" [Jacobson et al. 2011] or "Biharmonic
Coordinates" (2D complex barycentric coordinates) [Weber et al. 2012].
These weights minimize a discrete version of the squared Laplacian energy
subject to positional interpolation constraints at selected vertices
(point handles) and transformation interpolation constraints at regions
(region handles).
@tparam SType  should be a simple index type e.g. `int`,`size_t`
@param[in] V  #V by dim list of mesh vertex positions
@param[in] T  #T by dim+1 list of / triangle indices into V      if dim=2
                         \ tetrahedron indices into V   if dim=3
@param[in] S  #point-handles+#region-handles list of lists of selected vertices for
    each handle. Point handles should have singleton lists and region
    handles should have lists of size at least dim+1 (and these points
    should be in general position).
@param[out] W  #V by #points-handles+(#region-handles * dim+1) matrix of weights so
    that columns correspond to each handles generalized barycentric
    coordinates (for point-handles) or animation space weights (for region
    handles).
@return true only on success
    )");
}
