#include "default_types.h"
#include <igl/comb_cross_field.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_comb_cross_field(nb::module_ &m)
{
    m.def("comb_cross_field",
        [](
            const Eigen::MatrixXN& V,
            const Eigen::MatrixXI& F,
            const Eigen::MatrixXN& PD1,
            const Eigen::MatrixXN& PD2
        ) {
            Eigen::MatrixXN PD1_out, PD2_out;
            igl::comb_cross_field(V, F, PD1, PD2, PD1_out, PD2_out);
            return std::make_tuple(PD1_out, PD2_out);
        },
        "V"_a,
        "F"_a,
        "PD1"_a,
        "PD2"_a,
        R"(Computes principal matchings of the vectors of a cross field across face edges,
           and generates a combed cross field defined on the mesh faces
     
          @param[in]  V          #V by 3 eigen Matrix of mesh vertex 3D positions
          @param[in]  F          #F by 4 eigen Matrix of face (quad) indices
          @param[in]  PD1in      #F by 3 eigen Matrix of the first per face cross field vector
          @param[in]  PD2in      #F by 3 eigen Matrix of the second per face cross field vector
          @param[out] PD1out      #F by 3 eigen Matrix of the first combed cross field vector
          @param[out] PD2out      #F by 3 eigen Matrix of the second combed cross field vector
        )"
    );
}
