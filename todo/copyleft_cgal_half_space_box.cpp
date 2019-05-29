#include <npe.h>
#include <typedefs.h>






#include <igl/half_space_box.h>

const char* ds_half_space_box = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Construct a mesh of box (BV,BF) so that it contains the intersection of
       the half-space under the plane (P) and the bounding box of V, and does not
       contain any of the half-space above (P).
      
       Inputs:
         P  plane so that normal points away from half-space
         V  #V by 3 list of vertex positions
       Outputs:
         BV  #BV by 3 list of box vertex positions
         BF  #BF b3 list of box triangle indices into BV
)igl_Qu8mg5v7";

npe_function(half_space_box)
npe_doc(ds_half_space_box)

npe_arg(p, CGAL::Plane_3<CGAL::Epeck> &)
npe_arg(v, dense_float, dense_double)


npe_begin_code()

  Eigen::Matrix<CGAL::Epeck::FT, 8, 3> & bv;
  Eigen::Matrix<int, 12, 3> & bf;
  igl::  copyleft::  cgal::half_space_box(p, v, bv, bf);
  return std::make_tuple(npe::move(bv), npe::move(bf));

npe_end_code()
#include <igl/half_space_box.h>

const char* ds_half_space_box = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Inputs:
         p  3d point on plane
         n  3d vector of normal of plane pointing away from inside
         V  #V by 3 list of vertex positions
       Outputs:
         BV  #BV by 3 list of box vertex positions
         BF  #BF b3 list of box triangle indices into BV
)igl_Qu8mg5v7";

npe_function(half_space_box)
npe_doc(ds_half_space_box)

npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)
npe_arg(v, dense_float, dense_double)


npe_begin_code()

  Eigen::Matrix<CGAL::Epeck::FT, 8, 3> & bv;
  Eigen::Matrix<int, 12, 3> & bf;
  igl::  copyleft::  cgal::half_space_box(p, n, v, bv, bf);
  return std::make_tuple(npe::move(bv), npe::move(bf));

npe_end_code()
#include <igl/half_space_box.h>

const char* ds_half_space_box = R"igl_Qu8mg5v7(

Parameters
----------


Returns
-------


See also
--------


Notes
-----
None

Examples
--------

 Inputs:
         equ  plane equation: a*x+b*y+c*z + d = 0
         V  #V by 3 list of vertex positions
       Outputs:
         BV  #BV by 3 list of box vertex positions
         BF  #BF b3 list of box triangle indices into BV
)igl_Qu8mg5v7";

npe_function(half_space_box)
npe_doc(ds_half_space_box)

npe_arg(equ, dense_float, dense_double)
npe_arg(v, dense_float, dense_double)


npe_begin_code()

  Eigen::Matrix<CGAL::Epeck::FT, 8, 3> & bv;
  Eigen::Matrix<int, 12, 3> & bf;
  igl::  copyleft::  cgal::half_space_box(equ, v, bv, bf);
  return std::make_tuple(npe::move(bv), npe::move(bf));

npe_end_code()


