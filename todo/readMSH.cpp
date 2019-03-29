#include <npe.h>
#include <typedefs.h>






#include <igl/readMSH.h>

const char* ds_read_msh = R"igl_Qu8mg5v7(

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

 Read a mesh (e.g., tet mesh) from a gmsh .msh file
   
   Inputs:
     filename  path to .msh file
   Outputs:
      V  #V by 3 list of 3D mesh vertex positions
      T  #T by ss list of 3D ss-element indices into V (e.g., ss=4 for tets)
   Returns true on success
)igl_Qu8mg5v7";

npe_function(read_msh)
npe_doc(ds_read_msh)

npe_arg(filename, std::string &)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> t;
  igl::readMSH(filename, v, t);
  return std::make_tuple(npe::move(v), npe::move(t));

npe_end_code()


