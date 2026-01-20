#include "default_types.h"
#include <igl/bounding_box_diagonal.h>
#include <nanobind/nanobind.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl {
    auto bounding_box_diagonal(
	const nb::DRef<const Eigen::MatrixXd>& V
    ) {
	return igl::bounding_box_diagonal(V);
    }
}

void bind_bounding_box_diagonal(nb::module_ &m) {
    m.def("bounding_box_diagonal", &pyigl::bounding_box_diagonal,
	  "V"_a,
	  R"(Compute the length of the diagonal of a given meshes axis-aligned bounding

	  @param[in] V  #V by 3 list of vertex/point positions
	  @return length of bounding box diagonal)"
    );
}
