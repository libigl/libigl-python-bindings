#include <npe.h>
#include <typedefs.h>






#include <igl/partition.h>

const char* ds_partition = R"igl_Qu8mg5v7(

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

 PARTITION partition vertices into groups based on each
   vertex's vector: vertices with similar coordinates (close in 
   space) will be put in the same group.
  
   Inputs:
     W  #W by dim coordinate matrix
     k  desired number of groups default is dim
   Output:
     G  #W list of group indices (1 to k) for each vertex, such that vertex i 
       is assigned to group G(i)
     S  k  list of seed vertices
     D  #W list of squared distances for each vertex to it's corresponding
       closest seed
)igl_Qu8mg5v7";

npe_function(partition)
npe_doc(ds_partition)

npe_arg(w, Eigen::MatrixXd &)
npe_arg(k, int)


npe_begin_code()

  Eigen::Matrix<int, Eigen::Dynamic, 1> & g;
  Eigen::Matrix<int, Eigen::Dynamic, 1> & s;
  Eigen::Matrix<double, Eigen::Dynamic, 1> & d;
  igl::partition(w, k, g, s, d);
  return std::make_tuple(npe::move(g), npe::move(s), npe::move(d));

npe_end_code()


