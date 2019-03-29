#include <npe.h>
#include <typedefs.h>






#include <igl/triangle_fan.h>

const char* ds_triangle_fan = R"igl_Qu8mg5v7(

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

 Given a list of faces tessellate all of the "exterior" edges forming another
   list of 
  
   Inputs:
     E  #E by simplex_size-1  list of exterior edges (see exterior_edges.h)
   Outputs:
     cap  #cap by simplex_size  list of "faces" tessellating the boundary edges
)igl_Qu8mg5v7";

npe_function(triangle_fan)
npe_doc(ds_triangle_fan)

npe_arg(e, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::MatrixXi & cap;
  igl::triangle_fan(e, cap);
  return npe::move(cap);

npe_end_code()
#include <igl/triangle_fan.h>

const char* ds_triangle_fan = R"igl_Qu8mg5v7(

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

 In-line version
)igl_Qu8mg5v7";

npe_function(triangle_fan)
npe_doc(ds_triangle_fan)

npe_arg(e, Eigen::MatrixXi &)


npe_begin_code()

  igl::triangle_fan(e);
  return ;

npe_end_code()


