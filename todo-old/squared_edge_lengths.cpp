#include <npe.h>
#include <typedefs.h>
#include <igl/squared_edge_lengths.h>

const char* ds_squared_edge_lengths = R"igl_Qu8mg5v7(

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

 Constructs a list of squared lengths of edges opposite each index in a face
   (triangle/tet) list
  
   Templates:
     DerivedV derived from vertex positions matrix type: i.e. MatrixXd
     DerivedF derived from face indices matrix type: i.e. MatrixXi
     DerivedL derived from edge lengths matrix type: i.e. MatrixXd
   Inputs:
     V  eigen matrix #V by 3
     F  #F by 2 list of mesh edges
      or
     F  #F by 3 list of mesh faces (must be triangles)
      or
     T  #T by 4 list of mesh elements (must be tets)
   Outputs:
     L  #F by {1|3|6} list of edge lengths squared
       for edges, column of lengths
       for triangles, columns correspond to edges [1,2],[2,0],[0,1]
       for tets, columns correspond to edges
       [3 0],[3 1],[3 2],[1 2],[2 0],[0 1]
  
)igl_Qu8mg5v7";

npe_function(squared_edge_lengths)
npe_doc(ds_squared_edge_lengths)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenDense<npe_Scalar_> l;
  igl::squared_edge_lengths(v, f, l);
  return npe::move(l);

npe_end_code()


