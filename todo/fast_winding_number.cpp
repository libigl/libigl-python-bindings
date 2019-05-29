#include <npe.h>
#include <typedefs.h>
#include <igl/fast_winding_number.h>

const char* ds_fast_winding_number = R"igl_Qu8mg5v7(

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

 Generate the precomputation for the fast winding number for point data
   [Barill et. al 2018].
  
   Given a set of 3D points P, with normals N, areas A, along with octree
   data, and an expansion order, we define a taylor series expansion at each
   octree cell.
  
   The octree data is designed to come from igl::octree, and the areas
   (if not obtained at scan time), may be calculated using
   igl::copyleft::cgal::point_areas.
  
   Inputs:
     P  #P by 3 list of point locations
     N  #P by 3 list of point normals
     A  #P by 1 list of point areas
     point_indices  a vector of vectors, where the ith entry is a vector of
                    the indices into P that are the ith octree cell's points
     CH             #OctreeCells by 8, where the ith row is the indices of
                    the ith octree cell's children
     expansion_order    the order of the taylor expansion. We support 0,1,2.
   Outputs:
     CM  #OctreeCells by 3 list of each cell's center of mass
     R   #OctreeCells by 1 list of each cell's maximum distance of any point
         to the center of mass
     EC  #OctreeCells by #TaylorCoefficients list of expansion coefficients.
         (Note that #TaylorCoefficients = ∑_{i=1}^{expansion_order} 3^i)
  
)igl_Qu8mg5v7";

npe_function(fast_winding_number)
npe_doc(ds_fast_winding_number)

npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)
npe_arg(a, dense_float, dense_double)
npe_arg(point_indices, std::vector<std::vector<int> > &)
npe_arg(ch, dense_float, dense_double)
npe_arg(expansion_order, int)


npe_begin_code()

  EigenDense<npe_Scalar_> cm;
  EigenDense<npe_Scalar_> r;
  EigenDense<npe_Scalar_> ec;
  igl::fast_winding_number(p, n, a, point_indices, ch, expansion_order, cm, r, ec);
  return std::make_tuple(npe::move(cm), npe::move(r), npe::move(ec));

npe_end_code()
#include <igl/fast_winding_number.h>

const char* ds_fast_winding_number = R"igl_Qu8mg5v7(

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

 Evaluate the fast winding number for point data, with default expansion
   order and beta (both are set to 2).
  
   This function performes the precomputation and evaluation all in one.
   If you need to acess the precomuptation for repeated evaluations, use the
   two functions designed for exposed precomputation (described above).
  
   Inputs:
     P  #P by 3 list of point locations
     N  #P by 3 list of point normals
     A  #P by 1 list of point areas
     Q  #Q by 3 list of query points for the winding number
   Outputs:
     WN  #Q by 1 list of windinng number values at each query point
  
)igl_Qu8mg5v7";

npe_function(fast_winding_number)
npe_doc(ds_fast_winding_number)

npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)
npe_arg(a, dense_float, dense_double)
npe_arg(q, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> wn;
  igl::fast_winding_number(p, n, a, q, wn);
  return npe::move(wn);

npe_end_code()






#include <igl/fast_winding_number.h>

const char* ds_fast_winding_number = R"igl_Qu8mg5v7(

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

 Evaluate the fast winding number for point data, having already done the
   the precomputation
  
   Inputs:
     P  #P by 3 list of point locations
     N  #P by 3 list of point normals
     A  #P by 1 list of point areas
     point_indices  a vector of vectors, where the ith entry is a vector of
                    the indices into P that are the ith octree cell's points
     CH  #OctreeCells by 8, where the ith row is the indices of
         the ith octree cell's children
     CM  #OctreeCells by 3 list of each cell's center of mass
     R   #OctreeCells by 1 list of each cell's maximum distance of any point
         to the center of mass
     EC  #OctreeCells by #TaylorCoefficients list of expansion coefficients.
          (Note that #TaylorCoefficients = ∑_{i=1}^{expansion_order} 3^i)
     Q  #Q by 3 list of query points for the winding number
     beta  This is a Barnes-Hut style accuracy term that separates near feild
           from far field. The higher the beta, the more accurate and slower
           the evaluation. We reccommend using a beta value of 2. Note that
           for a beta value ≤ 0, we use the direct evaluation, rather than
           the fast approximation
   Outputs:
     WN  #Q by 1 list of windinng number values at each query point
  
)igl_Qu8mg5v7";

npe_function(fast_winding_number)
npe_doc(ds_fast_winding_number)

npe_arg(p, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)
npe_arg(a, dense_float, dense_double)
npe_arg(point_indices, std::vector<std::vector<int> > &)
npe_arg(ch, dense_float, dense_double)
npe_arg(cm, dense_float, dense_double)
npe_arg(r, dense_float, dense_double)
npe_arg(ec, dense_float, dense_double)
npe_arg(q, dense_float, dense_double)
npe_arg(beta, BetaType)


npe_begin_code()

  EigenDense<npe_Scalar_> wn;
  igl::fast_winding_number(p, n, a, point_indices, ch, cm, r, ec, q, beta, wn);
  return npe::move(wn);

npe_end_code()


