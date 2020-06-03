#include <npe.h>
#include <typedefs.h>
#include <igl/intrinsic_delaunay_triangulation.h>

const char* ds_intrinsic_delaunay_triangulation = R"igl_Qu8mg5v7(

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

 INTRINSIC_DELAUNAY_TRIANGULATION Flip edges _intrinsically_ until all are
   "intrinsic Delaunay". See "An algorithm for the construction of intrinsic
   delaunay triangulations with applications to digital geometry processing"
   [Fisher et al. 2007].
  
   Inputs:
     l_in  #F_in by 3 list of edge lengths (see edge_lengths)
     F_in  #F_in by 3 list of face indices into some unspecified vertex list V
   Outputs:
     l  #F by 3 list of edge lengths
     F  #F by 3 list of new face indices. Note: Combinatorially F may contain
       non-manifold edges, duplicate faces and self-loops (e.g., an edge [1,1]
       or a face [1,1,1]). However, the *intrinsic geometry* is still
       well-defined and correct. See [Fisher et al. 2007] Figure 3 and 2nd to
       last paragraph of 1st page. Since F may be "non-eddge-manifold" in the
       usual combinatorial sense, it may be useful to call the more verbose
       overload below if disentangling edges will be necessary later on.
       Calling unique_edge_map on this F will give a _different_ result than
       those outputs.
  
   See also: is_intrinsic_delaunay
)igl_Qu8mg5v7";

npe_function(intrinsic_delaunay_triangulation)
npe_doc(ds_intrinsic_delaunay_triangulation)

npe_arg(l_in, dense_f32, dense_f64)
npe_arg(f_in, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> l;
  EigenDense<npe_Scalar_> f;
  igl::intrinsic_delaunay_triangulation(l_in, f_in, l, f);
  return std::make_tuple(npe::move(l), npe::move(f));

npe_end_code()






#include <igl/intrinsic_delaunay_triangulation.h>

const char* ds_intrinsic_delaunay_triangulation = R"igl_Qu8mg5v7(

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

 Outputs:
     E  #F*3 by 2 list of all directed edges, such that E.row(f+#F*c) is the
       edge opposite F(f,c)
     uE  #uE by 2 list of unique undirected edges
     EMAP #F*3 list of indices into uE, mapping each directed edge to unique
       undirected edge
     uE2E  #uE list of lists of indices into E of coexisting edges
  
   See also: unique_edge_map
)igl_Qu8mg5v7";

npe_function(intrinsic_delaunay_triangulation)
npe_doc(ds_intrinsic_delaunay_triangulation)

npe_arg(l_in, dense_f32, dense_f64)
npe_arg(f_in, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> l;
  EigenDense<npe_Scalar_> f;
  EigenDense<npe_Scalar_> e;
  EigenDense<npe_Scalar_> u_e;
  EigenDense<npe_Scalar_> emap;
  std::vector<std::vector<uE2EType> > & u_e2_e;
  igl::intrinsic_delaunay_triangulation(l_in, f_in, l, f, e, u_e, emap, u_e2_e);
  return std::make_tuple(npe::move(l), npe::move(f), npe::move(e), npe::move(u_e), npe::move(emap), npe::move(u_e2_e));

npe_end_code()


