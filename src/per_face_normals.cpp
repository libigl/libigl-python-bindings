#include "default_types.h"
#include <igl/per_face_normals.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/eigen/dense.h>

namespace nb = nanobind;
using namespace nb::literals;

namespace pyigl
{
  // Wrapper for per_face_normals function
  nb::object per_face_normals_VF(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::RowVectorXN> &Z)
  {
    Eigen::MatrixXN N;
    igl::per_face_normals(V,F,Z,N);
    return nb::cast(std::move(N));
  }
  // Wrapper for per_face_normals function
  nb::object per_face_normals_VIC(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::VectorXI> &I,
    const nb::DRef<const Eigen::VectorXI> &C,
    const nb::DRef<const Eigen::RowVectorXN> &Z,
    const bool return_VV,
    const bool return_FF,
    const bool return_J)
  {
    Eigen::MatrixXN N;
    if(Z.size() > 0)
    {
      throw std::invalid_argument("per_face_normals: Z should not be provided for polygonal meshes");
    }
    Eigen::MatrixXN VV;
    Eigen::MatrixXI FF;
    Eigen::VectorXI J;
    igl::per_face_normals(V,I,C,N,VV,FF,J);
    if(return_VV && return_FF && return_J)
    {
      return nb::make_tuple(N,VV,FF,J);
    }else if(return_VV && return_FF)
    {
      return nb::make_tuple(N,VV,FF);
    }else if(return_VV && return_J)
    {
      return nb::make_tuple(N,VV,J);
    }else if(return_FF && return_J)
    {
      return nb::make_tuple(N,FF,J);
    }else if(return_VV)
    {
      return nb::make_tuple(N,VV);
    }else if(return_FF)
    {
      return nb::make_tuple(N,FF);
    }else if(return_J)
    {
      return nb::make_tuple(N,J);
    }
    
    return nb::cast(std::move(N));
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
    "Z"_a=Eigen::RowVectorXN(),
    "return_VV"_a=false,
    "return_FF"_a=false,
    "return_J"_a=false,
R"(Compute face normals via vertex position list, polygon stream

@param[in] V  #V by 3 eigen Matrix of mesh vertex 3D positions
@param[in] I  #I vectorized list of polygon corner indices into rows of some matrix V
@param[in] C  #polygons+1 list of cumulative polygon sizes so that C(i+1)-C(i) = size of
    the ith polygon, and so I(C(i)) through I(C(i+1)-1) are the indices of
    the ith polygon
@param[in] Z  3 vector normal given to faces with degenerate normal.
@param[in] return_VV  whether to return VV
@param[in] return_FF  whether to return FF
@param[in] return_J  whether to return J
@param[out] N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals
@param[out] VV  #I+#polygons by 3 list of auxiliary triangle mesh vertex positions
@param[out] FF  #I by 3 list of triangle indices into rows of VV
@param[out] J  #I list of indices into original polygons)"
    );
}
