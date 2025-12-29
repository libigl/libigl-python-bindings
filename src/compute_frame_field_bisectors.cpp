#include "default_types.h"
#include <igl/compute_frame_field_bisectors.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_compute_frame_field_bisectors(nb::module_ &m)
{
    m.def("compute_frame_field_bisectors",
        [](
        const Eigen::MatrixXN& V,
        const Eigen::MatrixXI& F,
        const Eigen::MatrixXN& B1,
        const Eigen::MatrixXN& B2,
        const Eigen::MatrixXN& PD1,
        const Eigen::MatrixXN& PD2
        ) {
            Eigen::MatrixXN BIS1, BIS2;
            igl::compute_frame_field_bisectors(V, F, B1, B2, PD1, PD2, BIS1, BIS2);
            return std::make_tuple(BIS1, BIS2);
        },
        "V"_a,
        "F"_a,
        "B1"_a,
        "B2"_a,
        "PD1"_a,
        "PD2"_a,
        R"(Compute bisectors of a frame field defined on mesh faces.

          @param[in] V     #V by 3 eigen Matrix of mesh vertex 3D positions
          @param[in] F     #F by 3 eigen Matrix of face (triangle) indices
          @param[in] B1    #F by 3 eigen Matrix of face (triangle) base vector 1
          @param[in] B2    #F by 3 eigen Matrix of face (triangle) base vector 2
          @param[in] PD1   #F by 3 eigen Matrix of the first per face frame field vector
          @param[in] PD2   #F by 3 eigen Matrix of the second per face frame field vector
          @param[out] BIS1  #F by 3 eigen Matrix of the first per face frame field bisector
          @param[out] BIS2  #F by 3 eigen Matrix of the second per face frame field bisector
        )"
    );

    // Overload
    m.def("compute_frame_field_bisectors",
        [](
        const Eigen::MatrixXN& V,
        const Eigen::MatrixXI& F,
        const Eigen::MatrixXN& PD1,
        const Eigen::MatrixXN& PD2
        ) {
            Eigen::MatrixXN BIS1, BIS2;
            igl::compute_frame_field_bisectors(V, F, PD1, PD2, BIS1, BIS2);
            return std::make_tuple(BIS1, BIS2);
        },
        "V"_a,
        "F"_a,
        "PD1"_a,
        "PD2"_a,
        R"(Compute bisectors of a frame field defined on mesh faces.

          @param[in] V     #V by 3 eigen Matrix of mesh vertex 3D positions
          @param[in] F     #F by 3 eigen Matrix of face (triangle) indices
          @param[in] PD1   #F by 3 eigen Matrix of the first per face frame field vector
          @param[in] PD2   #F by 3 eigen Matrix of the second per face frame field vector
          @param[out] BIS1  #F by 3 eigen Matrix of the first per face frame field bisector
          @param[out] BIS2  #F by 3 eigen Matrix of the second per face frame field bisector
        )"
    );
}
