#include <npe.h>
#include <typedefs.h>






#include <igl/knn.h>

const char* ds_knn = R"igl_Qu8mg5v7(

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

 Given a 3D set of points P, an whole number k, and an octree
   find the indicies of the k nearest neighbors for each point in P.
   Note that each point is its own neighbor.
  
   The octree data structures used in this function are intended to be the
   same ones output from igl::octree
  
   Inputs:
     P  #P by 3 list of point locations
     k  number of neighbors to find
     point_indices  a vector of vectors, where the ith entry is a vector of
                    the indices into P that are the ith octree cell's points
     CH     #OctreeCells by 8, where the ith row is the indices of
            the ith octree cell's children
     CN     #OctreeCells by 3, where the ith row is a 3d row vector
            representing the position of the ith cell's center
     W      #OctreeCells, a vector where the ith entry is the width
            of the ith octree cell
   Outputs:
     I  #P by k list of k-nearest-neighbor indices into P
)igl_Qu8mg5v7";

npe_function(knn)
npe_doc(ds_knn)

npe_arg(p, dense_float, dense_double)
npe_arg(k, KType &)
npe_arg(point_indices, std::vector<std::vector<IndexType> > &)
npe_arg(ch, dense_float, dense_double)
npe_arg(cn, dense_float, dense_double)
npe_arg(w, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> i;
  igl::knn(p, k, point_indices, ch, cn, w, i);
  return npe::move(i);

npe_end_code()


