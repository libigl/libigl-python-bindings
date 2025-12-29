#include "default_types.h"
#include <igl/cross_field_mismatch.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_cross_field_mismatch(nb::module_ &m)
{
    m.def("cross_field_mismatch",
        [](
            const Eigen::MatrixXN& V,
            const Eigen::MatrixXI& F,
            const Eigen::MatrixXN& PD1,
            const Eigen::MatrixXN& PD2,
            const bool isCombed
        ) {
            Eigen::MatrixXI mismatch;
            igl::cross_field_mismatch(V, F, PD1, PD2, isCombed, mismatch);
            return mismatch;
        },
        "V"_a,
        "F"_a,
        "PD1"_a,
        "PD2"_a,
        "isCombed"_a,
        R"(Calculates the mismatch (integer), at each face edge, of a cross field defined on the mesh faces.
           The integer mismatch is a multiple of pi/2 that transforms the cross on one side of the edge to
           the cross on the other side. It represents the deviation from a Lie connection across the edge.
         
           @param[in] V         #V by 3 eigen Matrix of mesh vertex 3D positions
           @param[in] F         #F by 3 eigen Matrix of face (quad) indices
           @param[in] PD1       #F by 3 eigen Matrix of the first per face cross field vector
           @param[in] PD2       #F by 3 eigen Matrix of the second per face cross field vector
           @param[in] isCombed  boolean, specifying whether the field is combed (i.e. matching has been precomputed.
                       If not, the field is combed first.
           @param[out] mismatch  #F by 3 eigen Matrix containing the integer mismatch of the cross field
                       across all face edges
        )"

    );
}
