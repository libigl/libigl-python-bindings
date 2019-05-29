#include <npe.h>
#include <typedefs.h>






#include <igl/mesh_boolean.h>

const char* ds_mesh_boolean = R"igl_Qu8mg5v7(

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

 Compute a boolean operation on two input meshes using the cork library.
      
       Inputs:
         VA  #VA by 3 list of vertex positions of first mesh
         FA  #FA by 3 list of triangle indices into VA
         VB  #VB by 3 list of vertex positions of second mesh
         FB  #FB by 3 list of triangle indices into VB
         type  of boolean operation see MeshBooleanType.h
       Outputs:
         VC  #VC by 3 list of vertex positions of output mesh
         FC  #FC by 3 list of triangle indices into VC
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)
npe_arg(type, igl::MeshBooleanType &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  igl::  copyleft::  cork::mesh_boolean(va, fa, vb, fb, type, vc, fc);
  return std::make_tuple(npe::move(vc), npe::move(fc));

npe_end_code()


