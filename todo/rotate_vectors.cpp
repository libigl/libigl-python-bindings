#include <npe.h>
#include <typedefs.h>






#include <igl/rotate_vectors.h>

const char* ds_rotate_vectors = R"igl_Qu8mg5v7(

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

 Rotate the vectors V by A radiants on the tangent plane spanned by B1 and
   B2
  
   Inputs:
     V     #V by 3 eigen Matrix of vectors
     A     #V eigen vector of rotation angles or a single angle to be applied
       to all vectors
     B1    #V by 3 eigen Matrix of base vector 1
     B2    #V by 3 eigen Matrix of base vector 2
  
   Output:
     Returns the rotated vectors
  
)igl_Qu8mg5v7";

npe_function(rotate_vectors)
npe_doc(ds_rotate_vectors)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(a, Eigen::VectorXd &)
npe_arg(b1, Eigen::MatrixXd &)
npe_arg(b2, Eigen::MatrixXd &)


npe_begin_code()

  igl::rotate_vectors(v, a, b1, b2);
  return ;

npe_end_code()


