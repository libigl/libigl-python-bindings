#include <npe.h>
#include <typedefs.h>






#include <igl/string_to_mesh_boolean_type.h>

const char* ds_string_to_mesh_boolean_type = R"igl_Qu8mg5v7(

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

 Convert string to boolean type
      
        Inputs:
          s  string identifying type, one of the following:
            "union","intersect","minus","xor","resolve"
        Outputs:
          type  type of boolean operation
       Returns true only on success
           
)igl_Qu8mg5v7";

npe_function(string_to_mesh_boolean_type)
npe_doc(ds_string_to_mesh_boolean_type)

npe_arg(s, std::string &)


npe_begin_code()

  igl::MeshBooleanType & type;
  igl::  copyleft::  cgal::string_to_mesh_boolean_type(s, type);
  return npe::move(type);

npe_end_code()
#include <igl/string_to_mesh_boolean_type.h>

const char* ds_string_to_mesh_boolean_type = R"igl_Qu8mg5v7(

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

 Returns type without error handling
)igl_Qu8mg5v7";

npe_function(string_to_mesh_boolean_type)
npe_doc(ds_string_to_mesh_boolean_type)

npe_arg(s, std::string &)


npe_begin_code()

  igl::  copyleft::  cgal::string_to_mesh_boolean_type(s);
  return ;

npe_end_code()


