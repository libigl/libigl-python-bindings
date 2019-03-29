#include <npe.h>
#include <typedefs.h>






#include <igl/transpose_blocks.h>

const char* ds_transpose_blocks = R"igl_Qu8mg5v7(

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

 Templates:
     T  should be a eigen matrix primitive type like int or double
   Inputs:
     A  m*k by n (dim: 1) or m by n*k (dim: 2) eigen Matrix of type T values
     k  number of blocks
     dim  dimension in which to transpose
   Output
     B  n*k by m (dim: 1) or n by m*k (dim: 2) eigen Matrix of type T values,
     NOT allowed to be the same as A
  
   Example:
   A = [
     1   2   3   4
     5   6   7   8
   101 102 103 104
   105 106 107 108
   201 202 203 204
   205 206 207 208];
   transpose_blocks(A,1,3,B);
   B -> [
     1   5
     2   6
     3   7
     4   8
   101 105
   102 106
   103 107
   104 108
   201 205
   202 206
   203 207
   204 208];
     
)igl_Qu8mg5v7";

npe_function(transpose_blocks)
npe_doc(ds_transpose_blocks)

npe_arg(a, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &)
npe_arg(k, size_t)
npe_arg(dim, size_t)


npe_begin_code()

  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> & b;
  igl::transpose_blocks(a, k, dim, b);
  return npe::move(b);

npe_end_code()


