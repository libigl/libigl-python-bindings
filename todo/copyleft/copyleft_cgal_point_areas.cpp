#include <npe.h>
#include <typedefs.h>
#include <igl/point_areas.h>

const char* ds_point_areas = R"igl_Qu8mg5v7(

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

 Given a 3D set of points P, each with a list of k-nearest-neighbours,
     estimate the geodesic voronoi area associated with each point.
    
     The k nearest neighbours may be known from running igl::knn_octree on
     the output data from igl::octree. We reccomend using a k value
     between 15 and 20 inclusive for accurate area estimation.
    
     N is used filter the neighbours, to ensure area estimation only occurs
     using neighbors that are on the same side of the surface (ie for thin
     sheets), as well as to solve the orientation ambiguity of the tangent
     plane normal.
    
     Note: This function *should* be implemented by pre-filtering I, rather
     than filtering in this function using N. In this case, the function
     would only take P and I as input.
    
     Inputs:
       P  #P by 3 list of point locations
       I  #P by k list of k-nearest-neighbor indices into P
       N  #P by 3 list of point normals
     Outputs:
       A  #P list of estimated areas
)igl_Qu8mg5v7";

npe_function(point_areas)
npe_doc(ds_point_areas)

npe_arg(p, dense_float, dense_double)
npe_arg(i, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> a;
  igl::  copyleft::  cgal::point_areas(p, i, n, a);
  return npe::move(a);

npe_end_code()
#include <igl/point_areas.h>

const char* ds_point_areas = R"igl_Qu8mg5v7(

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

 This version can be used to output the tangent plane normal at each
     point. Since we area already fitting a plane to each point's neighbour
     set, the tangent plane normals come "for free"
    
     Inputs:
       P  #P by 3 list of point locations
       I  #P by k list of k-nearest-neighbor indices into P
       N  #P by 3 list of point normals
     Outputs:
       A  #P list of estimated areas
       T  #P by 3 list of tangent plane normals for each point
)igl_Qu8mg5v7";

npe_function(point_areas)
npe_doc(ds_point_areas)

npe_arg(p, dense_float, dense_double)
npe_arg(i, dense_float, dense_double)
npe_arg(n, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> a;
  EigenDense<npe_Scalar_> t;
  igl::  copyleft::  cgal::point_areas(p, i, n, a, t);
  return std::make_tuple(npe::move(a), npe::move(t));

npe_end_code()


