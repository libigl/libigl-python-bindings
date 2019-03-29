#include <npe.h>
#include <typedefs.h>
#include <igl/cotmatrix_entries.h>

const char* ds_cotmatrix_entries = R"igl_Qu8mg5v7(

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

 COTMATRIX_ENTRIES compute the cotangents of each angle in mesh (V,F)
   
   Inputs:
     V  #V by dim list of rest domain positions
     F  #F by {3|4} list of {triangle|tetrahedra} indices into V
   Outputs:
       C  #F by 3 list of 1/2*cotangents corresponding angles
         for triangles, columns correspond to edges [1,2],[2,0],[0,1]
     OR
       C  #F by 6 list of 1/6*cotangents of dihedral angles*edge lengths
         for tets, columns along edges [1,2],[2,0],[0,1],[3,0],[3,1],[3,2] 
  
)igl_Qu8mg5v7";

npe_function(cotmatrix_entries)
npe_doc(ds_cotmatrix_entries)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> c;
  igl::cotmatrix_entries(v, f, c);
  return npe::move(c);

npe_end_code()


