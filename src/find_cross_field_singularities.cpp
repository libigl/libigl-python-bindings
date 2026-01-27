#include "default_types.h"
#include <igl/find_cross_field_singularities.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_find_cross_field_singularities(nb::module_ &m)
{
    m.def("find_cross_field_singularities",
        [](
            const Eigen::MatrixXN& V,
            const Eigen::MatrixXI& F,
            const Eigen::MatrixXI& mismatch
        ) {
            Eigen::VectorXI isSingularity, singularityIndex;
            igl::find_cross_field_singularities(V, F, mismatch, isSingularity, singularityIndex);
            return std::make_tuple(isSingularity, singularityIndex);
        },
        "V"_a,
        "F"_a,
        "mismatch"_a,
        R"(Computes singularities of a cross field, assumed combed
     
           @param[in] V                #V by 3 eigen Matrix of mesh vertex 3D positions
           @param[in] F                #F by 3 eigen Matrix of face (quad) indices
           @param[in] mismatch         #F by 3 eigen Matrix containing the integer mismatch of the cross field
                              across all face edges
           @param[out] isSingularity    #V by 1 boolean eigen Vector indicating the presence of a singularity on a vertex
           @param[out] singularityIndex #V by 1 integer eigen Vector containing the singularity indices
        )"
    );

    // overload
    m.def("find_cross_field_singularities",
        [](
            const Eigen::MatrixXN& V,
            const Eigen::MatrixXI& F,
            const Eigen::MatrixXN& PD1,
            const Eigen::MatrixXN& PD2,
            bool isCombed
        ) {
            Eigen::VectorXI isSingularity, singularityIndex;
            igl::find_cross_field_singularities(V, F, PD1, PD2, isSingularity, singularityIndex, isCombed);
            return std::make_tuple(isSingularity, singularityIndex);
        },
        "V"_a,
        "F"_a,
        "PD1"_a,
        "PD2"_a,
        "isCombed"_a = false,
        R"(Wrapper that calculates the mismatch if it is not provided.
     
           @param[in] PD1              #F by 3 eigen Matrix of the first per face cross field vector
           @param[in] PD2              #F by 3 eigen Matrix of the second per face  cross field vector
           @param[in] isCombed        boolean indicating whether the cross field is combed
         
           \note the field in PD1 and PD2 MUST BE combed (see igl::comb_cross_field).
        )"
    );
}
