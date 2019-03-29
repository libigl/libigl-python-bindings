#include <npe.h>
#include <typedefs.h>






#include <igl/mvc.h>

const char* ds_mvc = R"igl_Qu8mg5v7(

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

   MVC - MEAN VALUE COORDINATES
    
     mvc(V,C,W)
    
     Inputs:
      V  #V x dim list of vertex positions (dim = 2 or dim = 3)
      C  #C x dim list of polygon vertex positions in counter-clockwise order
        (dim = 2 or dim = 3)
    
     Outputs:
      W  weights, #V by #C matrix of weights
    
    Known Bugs: implementation is listed as "Broken"
)igl_Qu8mg5v7";

npe_function(mvc)
npe_doc(ds_mvc)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(c, Eigen::MatrixXd &)


npe_begin_code()

  Eigen::MatrixXd & w;
  igl::mvc(v, c, w);
  return npe::move(w);

npe_end_code()


