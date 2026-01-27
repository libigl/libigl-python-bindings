#include "default_types.h"
#include <igl/rotate_vectors.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

void bind_rotate_vectors(nb::module_ &m) {
  m.def(
      "rotate_vectors",
      [](const Eigen::MatrixXN &V, const Eigen::VectorXN &A,
         const Eigen::MatrixXN &B1, const Eigen::MatrixXN &B2) {
        return igl::rotate_vectors(V, A, B1, B2);
      },
      "V"_a, "A"_a, "B1"_a, "B2"_a,
      R"(Rotate the vectors V by A radians on the tangent plane spanned by B1 and B2
     
          @param[in] V     #V by 3 eigen Matrix of vectors
          @param[in] A     #V eigen vector of rotation angles or a single angle to be applied
                           to all vectors
          @param[in] B1    #V by 3 eigen Matrix of base vector 1
          @param[in] B2    #V by 3 eigen Matrix of base vector 2
          @return the rotated vectors
        )");
}
