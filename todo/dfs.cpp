#include <npe.h>
#include <typedefs.h>






#include <igl/dfs.h>

const char* ds_dfs = R"igl_Qu8mg5v7(

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

 Traverse a **directed** graph represented by an adjacency list using
   depth first search
  
   Inputs:
     A  #V list of adjacency lists
     s  starting node (index into A)
   Outputs:
     D  #V list of indices into rows of A in the order in which graph nodes
       are discovered.
     P  #V list of indices into rows of A of predecessor in resulting
       spanning tree {-1 indicates root/not discovered), order corresponds to
       V **not** D.
     C  #V list of indices into rows of A in order that nodes are "closed"
       (all descendants have been discovered)
)igl_Qu8mg5v7";

npe_function(dfs)
npe_doc(ds_dfs)

npe_arg(a, std::vector<std::vector<AType> > &)
npe_arg(s, size_t)


npe_begin_code()

  EigenDense<npe_Scalar_> d;
  EigenDense<npe_Scalar_> p;
  EigenDense<npe_Scalar_> c;
  igl::dfs(a, s, d, p, c);
  return std::make_tuple(npe::move(d), npe::move(p), npe::move(c));

npe_end_code()
#include <igl/dfs.h>

const char* ds_dfs = R"igl_Qu8mg5v7(
See dfs for the documentation.
)igl_Qu8mg5v7";

npe_function(dfs)
npe_doc(ds_dfs)

npe_arg(a, std::vector<std::vector<AType> > &)
npe_arg(s, size_t)


npe_begin_code()

  std::vector<DType> & d;
  std::vector<PType> & p;
  std::vector<CType> & c;
  igl::dfs(a, s, d, p, c);
  return std::make_tuple(npe::move(d), npe::move(p), npe::move(c));

npe_end_code()


