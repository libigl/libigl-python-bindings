#include "default_types.h"
#include <igl/per_face_normals.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for per_face_normals function
  auto per_face_normals_VF(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::RowVectorXN> &Z)
  {
    Eigen::MatrixXN N;
    igl::per_face_normals(V,F,Z,N);
    return N;
  }
  // Wrapper for per_face_normals function
  auto per_face_normals_VIC(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::VectorXI> &I,
    const nb::DRef<const Eigen::VectorXI> &C)
  {
    Eigen::MatrixXN N;
    Eigen::MatrixXN VV;
    Eigen::MatrixXI FF;
    Eigen::VectorXI J;
    igl::per_face_normals(V,I,C,N,VV,FF,J);
    return std::make_tuple(N,VV,FF,J);
  }
}

// Bind the wrapper to the Python module
void bind_per_face_normals(nb::module_ &m)
{
  m.def(
    "per_face_normals",
    &pyigl::per_face_normals_VF,
    "V"_a, 
    "F"_a,
    "Z"_a=Eigen::RowVectorXN(),
R"(Compute face normals via vertex position list, face list

@param[in] V  #V by 3 eigen Matrix of mesh vertex 3D positions
@param[in] F  #F by 3 eigen Matrix of face (triangle) indices
@param[in] Z  3 vector normal given to faces with degenerate normal.
@param[out] N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals)"
    );
  m.def(
    "per_face_normals",
    &pyigl::per_face_normals_VIC,
    "V"_a, 
    "I"_a,
    "C"_a,
R"(Compute face normals via vertex position list, polygon stream

@param[in] V  #V by 3 eigen Matrix of mesh vertex 3D positions
@param[in] I  #I vectorized list of polygon corner indices into rows of some matrix V
@param[in] C  #polygons+1 list of cumulative polygon sizes so that C(i+1)-C(i) = size of
    the ith polygon, and so I(C(i)) through I(C(i+1)-1) are the indices of
    the ith polygon
@param[out] N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals
@param[out] VV  #I+#polygons by 3 list of auxiliary triangle mesh vertex positions
@param[out] FF  #I by 3 list of triangle indices into rows of VV
@param[out] J  #I list of indices into original polygons)"
    );
}
