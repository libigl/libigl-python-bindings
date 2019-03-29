#include <npe.h>
#include <typedefs.h>
#include <igl/face_areas.h>

const char* ds_face_areas = R"igl_Qu8mg5v7(

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

 Constructs a list of face areas of faces opposite each index in a tet list
  
   Inputs:
     V  #V by 3 list of mesh vertex positions
     T  #T by 3 list of tet mesh indices into V
   Outputs:
     A   #T by 4 list of face areas corresponding to faces opposite vertices
       0,1,2,3
  
)igl_Qu8mg5v7";

npe_function(face_areas)
npe_doc(ds_face_areas)

npe_arg(v, dense_f32, dense_f64)
npe_arg(t, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> a;
  igl::face_areas(v, t, a);
  return npe::move(a);

npe_end_code()
#include <igl/face_areas.h>

const char* ds_face_areas = R"igl_Qu8mg5v7(

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

 Compute tet-mesh face areas from edge lengths.
  
   Inputs:
     L  #T by 6 list of tet-mesh edge lengths corresponding to edges
       [3 0],[3 1],[3 2],[1 2],[2 0],[0 1]
   Outputs:
     A   #T by 4 list of face areas corresponding to faces opposite vertices 
       0,1,2,3: i.e. made of edges [123],[024],[015],[345]
      
  
)igl_Qu8mg5v7";

npe_function(face_areas)
npe_doc(ds_face_areas)

npe_arg(l, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> a;
  igl::face_areas(l, a);
  return npe::move(a);

npe_end_code()






#include <igl/face_areas.h>

const char* ds_face_areas = R"igl_Qu8mg5v7(

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

 doublearea_nan_replacement  See doublearea.h
)igl_Qu8mg5v7";

npe_function(face_areas)
npe_doc(ds_face_areas)

npe_arg(l, dense_f32, dense_f64)
npe_arg(doublearea_nan_replacement, typename DerivedL::Scalar)


npe_begin_code()

  EigenDense<npe_Scalar_> a;
  igl::face_areas(l, doublearea_nan_replacement, a);
  return npe::move(a);

npe_end_code()


