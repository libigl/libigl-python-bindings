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
  nb::object per_face_normals(
    const nb::DRef<const Eigen::MatrixXN> &V,
    const nb::DRef<const Eigen::MatrixXI> &F,
    const nb::DRef<const Eigen::VectorXI> &I,
    const nb::DRef<const Eigen::VectorXI> &C,
    const nb::DRef<const Eigen::RowVectorXN> &Z,
    const bool return_VV,
    const bool return_FF,
    const bool return_J)
  {
    Eigen::MatrixXN N;
    if(I.size() > 0)
    {
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
    }else
    {
      if(return_VV || return_FF || return_J)
      {
        throw std::runtime_error("per_face_normals: VV, FF, and J only available for polygonal meshes");
      }
      igl::per_face_normals(V,F,Z,N);
    }
    return nb::cast(N);
  }
}

// Bind the wrapper to the Python module
void bind_per_face_normals(nb::module_ &m)
{
  m.def(
    "per_face_normals",
    &pyigl::per_face_normals,
    "V"_a, 
    "F"_a=Eigen::MatrixXI(),
    "I"_a=Eigen::VectorXI(),
    "C"_a=Eigen::VectorXI(),
    "Z"_a=Eigen::RowVectorXN(),
    "return_VV"_a=false,
    "return_FF"_a=false,
    "return_J"_a=false,
R"(Compute face normals via vertex position list, face list

@param[in] V  #V by 3 eigen Matrix of mesh vertex 3D positions
@param[in] F  #F by 3 eigen Matrix of face (triangle) indices
@param[in] Z  3 vector normal given to faces with degenerate normal.
@param[out] N  #F by 3 eigen Matrix of mesh face (triangle) 3D normals)"
    );
}
