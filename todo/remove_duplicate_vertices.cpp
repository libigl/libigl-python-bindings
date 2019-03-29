#include <npe.h>
#include <typedefs.h>






#include <igl/remove_duplicate_vertices.h>

const char* ds_remove_duplicate_vertices = R"igl_Qu8mg5v7(

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

 REMOVE_DUPLICATE_VERTICES Remove duplicate vertices upto a uniqueness
   tolerance (epsilon)
  
   Inputs:
     V  #V by dim list of vertex positions
     epsilon  uniqueness tolerance (significant digit), can probably think of
       this as a tolerance on L1 distance
   Outputs:
     SV  #SV by dim new list of vertex positions
     SVI #V by 1 list of indices so SV = V(SVI,:) 
     SVJ #SV by 1 list of indices so V = SV(SVJ,:)
  
   Example:
     % Mesh in (V,F)
     [SV,SVI,SVJ] = remove_duplicate_vertices(V,1e-7);
     % remap faces
     SF = SVJ(F);
  
)igl_Qu8mg5v7";

npe_function(remove_duplicate_vertices)
npe_doc(ds_remove_duplicate_vertices)

npe_arg(v, dense_f32, dense_f64)
npe_arg(epsilon, double)


npe_begin_code()

  EigenDense<npe_Scalar_> sv;
  EigenDense<npe_Scalar_> svi;
  EigenDense<npe_Scalar_> svj;
  igl::remove_duplicate_vertices(v, epsilon, sv, svi, svj);
  return std::make_tuple(npe::move(sv), npe::move(svi), npe::move(svj));

npe_end_code()
#include <igl/remove_duplicate_vertices.h>

const char* ds_remove_duplicate_vertices = R"igl_Qu8mg5v7(

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

 Wrapper that also remaps given faces (F) --> (SF) so that SF index SV
)igl_Qu8mg5v7";

npe_function(remove_duplicate_vertices)
npe_doc(ds_remove_duplicate_vertices)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(epsilon, double)


npe_begin_code()

  EigenDense<npe_Scalar_> sv;
  EigenDense<npe_Scalar_> svi;
  EigenDense<npe_Scalar_> svj;
  EigenDense<npe_Scalar_> sf;
  igl::remove_duplicate_vertices(v, f, epsilon, sv, svi, svj, sf);
  return std::make_tuple(npe::move(sv), npe::move(svi), npe::move(svj), npe::move(sf));

npe_end_code()


