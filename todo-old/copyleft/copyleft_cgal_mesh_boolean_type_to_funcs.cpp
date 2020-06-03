#include <npe.h>
#include <typedefs.h>






#include <igl/mesh_boolean_type_to_funcs.h>

const char* ds_mesh_boolean_type_to_funcs = R"igl_Qu8mg5v7(

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

 Convert a MeshBooleanType enum to a pair of winding number conversion
       function and "keep" function used by mesh_boolean
      
       Inputs:
         type  MeshBooleanType enum value
       Outputs:
          wind_num_op  function handle for filtering winding numbers from
            tuples of integer values to [0,1] outside/inside values
          keep  function handle for determining if a patch should be "kept"
            in the output based on the winding number on either side
      
       See also: string_to_mesh_boolean_type
)igl_Qu8mg5v7";

npe_function(mesh_boolean_type_to_funcs)
npe_doc(ds_mesh_boolean_type_to_funcs)

npe_arg(type, igl::MeshBooleanType &)


npe_begin_code()

  std::function<int (const Eigen::Matrix<int, 1, Eigen::Dynamic>)> & wind_num_op;
  std::function<int (const int, const int)> & keep;
  igl::  copyleft::  cgal::mesh_boolean_type_to_funcs(type, wind_num_op, keep);
  return std::make_tuple(npe::move(wind_num_op), npe::move(keep));

npe_end_code()


