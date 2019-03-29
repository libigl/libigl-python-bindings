#include <npe.h>
#include <typedefs.h>
#include <igl/internal_angles.h>

const char* ds_internal_angles = R"igl_Qu8mg5v7(

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

 Compute internal angles for a triangle mesh
  
   Inputs:
     V  #V by dim eigen Matrix of mesh vertex nD positions
     F  #F by poly-size eigen Matrix of face (triangle) indices
   Output:
     K  #F by poly-size eigen Matrix of internal angles
       for triangles, columns correspond to edges [1,2],[2,0],[0,1]
  
   Known Issues:
     if poly-size ≠ 3 then dim must equal 3.
)igl_Qu8mg5v7";

npe_function(internal_angles)
npe_doc(ds_internal_angles)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> k;
  igl::internal_angles(v, f, k);
  return npe::move(k);

npe_end_code()
#include <igl/internal_angles_using_squared_edge_lengths.h>

const char* ds_internal_angles_using_squared_edge_lengths = R"igl_Qu8mg5v7(

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

 Inputs:
     L_sq  #F by 3 list of squared edge lengths
   Output:
     K  #F by poly-size eigen Matrix of internal angles
       for triangles, columns correspond to edges [1,2],[2,0],[0,1]
  
   Note:
     Usage of internal_angles_using_squared_edge_lengths is preferred to internal_angles_using_squared_edge_lengths
)igl_Qu8mg5v7";

npe_function(internal_angles_using_squared_edge_lengths)
npe_doc(ds_internal_angles_using_squared_edge_lengths)

npe_arg(l_sq, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> k;
  igl::internal_angles_using_squared_edge_lengths(l_sq, k);
  return npe::move(k);

npe_end_code()
#include <igl/internal_angles_using_edge_lengths.h>

const char* ds_internal_angles_using_edge_lengths = R"igl_Qu8mg5v7(

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

 Inputs:
     L  #F by 3 list of edge lengths
   Output:
     K  #F by poly-size eigen Matrix of internal angles
       for triangles, columns correspond to edges [1,2],[2,0],[0,1]
  
   Note:
     Usage of internal_angles_using_squared_edge_lengths is preferred to internal_angles_using_squared_edge_lengths
     This function is deprecated and probably will be removed in future versions
)igl_Qu8mg5v7";

npe_function(internal_angles_using_edge_lengths)
npe_doc(ds_internal_angles_using_edge_lengths)

npe_arg(l, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> k;
  igl::internal_angles_using_edge_lengths(l, k);
  return npe::move(k);

npe_end_code()


