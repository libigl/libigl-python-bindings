#include <npe.h>
#include <typedefs.h>
#include <igl/boundary_loop.h>

const char* ds_boundary_loop = R"igl_Qu8mg5v7(

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

 Compute list of ordered boundary loops for a manifold mesh.
  
   Templates:
    Index  index type
   Inputs:
     F  #V by dim list of mesh faces
   Outputs:
     L  list of loops where L[i] = ordered list of boundary vertices in loop i
  
)igl_Qu8mg5v7";

npe_function(boundary_loop)
npe_doc(ds_boundary_loop)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  std::vector<std::vector<int> > & l;
  igl::boundary_loop(f, l);
  return npe::move(l);

npe_end_code()
#include <igl/boundary_loop.h>

const char* ds_boundary_loop = R"igl_Qu8mg5v7(

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

 Compute ordered boundary loops for a manifold mesh and return the 
   longest loop in terms of vertices.
  
   Templates:
    Index  index type
   Inputs:
     F  #V by dim list of mesh faces
   Outputs:
     L  ordered list of boundary vertices of longest boundary loop
  
)igl_Qu8mg5v7";

npe_function(boundary_loop)
npe_doc(ds_boundary_loop)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> l;
  igl::boundary_loop(f, l);
  return npe::move(l);

npe_end_code()






#include <igl/boundary_loop.h>

const char* ds_boundary_loop = R"igl_Qu8mg5v7(

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

 Compute ordered boundary loops for a manifold mesh and return the 
   longest loop in terms of vertices.
  
   Templates:
    Index  index type
   Inputs:
     F  #V by dim list of mesh faces
   Outputs:
     L  ordered list of boundary vertices of longest boundary loop
  
)igl_Qu8mg5v7";

npe_function(boundary_loop)
npe_doc(ds_boundary_loop)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  std::vector<Index> & l;
  igl::boundary_loop(f, l);
  return npe::move(l);

npe_end_code()


