#include <npe.h>
#include <typedefs.h>






#include <igl/directed_edge_orientations.h>

const char* ds_directed_edge_orientations = R"igl_Qu8mg5v7(

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

 Determine rotations that take each edge from the x-axis to its given rest
   orientation.
  
   Inputs:
     C  #C by 3 list of edge vertex positions
     E  #E by 2 list of directed edges
   Outputs:
     Q  #E list of quaternions 
  
)igl_Qu8mg5v7";

npe_function(directed_edge_orientations)
npe_doc(ds_directed_edge_orientations)

npe_arg(c, dense_f32, dense_f64)
npe_arg(e, dense_f32, dense_f64)


npe_begin_code()

  std::vector<Eigen::Quaterniond, Eigen::aligned_allocator<Eigen::Quaterniond> > & q;
  igl::directed_edge_orientations(c, e, q);
  return npe::move(q);

npe_end_code()


