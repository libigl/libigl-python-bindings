#include <npe.h>
#include <typedefs.h>






#include <igl/combine.h>

const char* ds_combine = R"igl_Qu8mg5v7(

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

 Concatenate k meshes into a single >=k connected component mesh with a
   single vertex list and face list. Similar to Maya's Combine operation. 
  
   Inputs:
     VV  k-long list of lists of mesh vertex positions
     FF  k-long list of lists of mesh face indices so that FF[i] indexes
       VV[i]
   Outputs:
     V   VV[0].rows()+...+VV[k-1].rows() by VV[0].cols() list of mesh
       vertex positions
     F   FF[0].rows()+...+FF[k-1].rows() by FF[0].cols() list of mesh faces
       indices into V
     Vsizes  k list so that Vsizes(i) is the #vertices in the ith input
     Fsizes  k list so that Fsizes(i) is the #faces in the ith input
   Example:
      Suppose you have mesh A (VA,FA) and mesh B (VB,FB)
     igl::combine<Eigen::MatrixXd,Eigen::MatrixXi>({VA,VB},{FA,FB},V,F);
  
  
)igl_Qu8mg5v7";

npe_function(combine)
npe_doc(ds_combine)

npe_arg(vv, std::vector<DerivedVV> &)
npe_arg(ff, std::vector<DerivedFF> &)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  EigenDense<npe_Scalar_> vsizes;
  EigenDense<npe_Scalar_> fsizes;
  igl::combine(vv, ff, v, f, vsizes, fsizes);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(vsizes), npe::move(fsizes));

npe_end_code()
#include <igl/combine.h>

const char* ds_combine = R"igl_Qu8mg5v7(
See combine for the documentation.
)igl_Qu8mg5v7";

npe_function(combine)
npe_doc(ds_combine)

npe_arg(vv, std::vector<DerivedVV> &)
npe_arg(ff, std::vector<DerivedFF> &)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  igl::combine(vv, ff, v, f);
  return std::make_tuple(npe::move(v), npe::move(f));

npe_end_code()


