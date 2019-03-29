#include <npe.h>
#include <typedefs.h>






#include <igl/map_vertices_to_circle.h>

const char* ds_map_vertices_to_circle = R"igl_Qu8mg5v7(

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

 Map the vertices whose indices are in a given boundary loop (bnd) on the
   unit circle with spacing proportional to the original boundary edge
   lengths.
  
   Inputs:
     V  #V by dim list of mesh vertex positions
     b  #W list of vertex ids
   Outputs:
     UV   #W by 2 list of 2D position on the unit circle for the vertices in b
)igl_Qu8mg5v7";

npe_function(map_vertices_to_circle)
npe_doc(ds_map_vertices_to_circle)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(bnd, Eigen::VectorXi &)


npe_begin_code()

  Eigen::MatrixXd & uv;
  igl::map_vertices_to_circle(v, bnd, uv);
  return npe::move(uv);

npe_end_code()


