#include <npe.h>
#include <typedefs.h>
#include <igl/extract_manifold_patches.h>

const char* ds_extract_manifold_patches = R"igl_Qu8mg5v7(
See extract_manifold_patches for the documentation.
)igl_Qu8mg5v7";

npe_function(extract_manifold_patches)
npe_doc(ds_extract_manifold_patches)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> p;
  igl::extract_manifold_patches(f, p);
  return npe::move(p);

npe_end_code()






#include <igl/extract_manifold_patches.h>

const char* ds_extract_manifold_patches = R"igl_Qu8mg5v7(

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

 Extract a set of maximal patches from a given mesh.
     A maximal patch is a subset of the input faces that are connected via
     manifold edges; a patch is as large as possible.
    
     Inputs:
       F  #F by 3 list representing triangles.
       EMAP  #F*3 list of indices of unique undirected edges.
       uE2E  #uE list of lists of indices into E of coexisting edges.
    
     Output:
       P  #F list of patch incides.
    
     Returns:
       number of manifold patches.
)igl_Qu8mg5v7";

npe_function(extract_manifold_patches)
npe_doc(ds_extract_manifold_patches)

npe_arg(f, dense_i32, dense_i64)
npe_arg(emap, dense_f32, dense_f64)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)


npe_begin_code()

  EigenDense<npe_Scalar_> p;
  igl::extract_manifold_patches(f, emap, u_e2_e, p);
  return npe::move(p);

npe_end_code()


