#pragma once
#include "default_types.h"
#include <Eigen/Geometry>
#include <stdexcept>
#include <string>
#include <vector>

namespace pyigl
{
  typedef Eigen::Transform<Numeric,3,Eigen::Affine> AffineN3;
  typedef std::vector<AffineN3,Eigen::aligned_allocator<AffineN3> > AffineN3List;

  /// Convert a Python list of 4×4 (or 3×4) matrices into the list of
  /// Eigen::Transforms that the igl::swept_volume* functions expect.
  ///
  /// @param[in] transforms  #transforms list of 4×4 or 3×4 matrices
  /// @param[in] caller  name used to prefix error messages
  /// @return #transforms list of affine transformations
  inline AffineN3List parse_transforms(
    const std::vector<Eigen::MatrixXN> &transforms,
    const char * const caller)
  {
    if(transforms.empty())
    {
      throw std::runtime_error(
        std::string(caller)+": transforms must be non-empty");
    }
    AffineN3List T;
    T.reserve(transforms.size());
    for(const auto & M : transforms)
    {
      if(M.cols() != 4 || (M.rows() != 3 && M.rows() != 4))
      {
        throw std::runtime_error(
          std::string(caller)+": each transform must be 3×4 or 4×4");
      }
      AffineN3 Ti;
      // A 3×4 input leaves the implicit bottom row as [0 0 0 1]
      Ti.matrix().setIdentity();
      Ti.matrix().topRows(M.rows()) = M;
      T.emplace_back(Ti);
    }
    return T;
  }
}
