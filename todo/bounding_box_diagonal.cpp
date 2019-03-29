#include <npe.h>
#include <typedefs.h>






#include <igl/bounding_box_diagonal.h>

const char* ds_bounding_box_diagonal = R"igl_Qu8mg5v7(

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

 Compute the length of the diagonal of a given meshes axis-aligned bounding
   box
  
   Inputs:
     V  #V by 3 list of vertex positions
     F  #F by 3 list of triangle indices into V
   Returns length of bounding box diagonal
)igl_Qu8mg5v7";

npe_function(bounding_box_diagonal)
npe_doc(ds_bounding_box_diagonal)

npe_arg(v, Eigen::MatrixXd &)


npe_begin_code()

  igl::bounding_box_diagonal(v);
  return ;

npe_end_code()


