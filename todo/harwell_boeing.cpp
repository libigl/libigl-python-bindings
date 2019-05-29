#include <npe.h>
#include <typedefs.h>






#include <igl/harwell_boeing.h>

const char* ds_harwell_boeing = R"igl_Qu8mg5v7(

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

 Convert the matrix to Compressed sparse column (CSC or CCS) format,
   also known as Harwell Boeing format. As described:
   http:netlib.org/linalg/html_templates/node92.html
   or
   http:en.wikipedia.org/wiki/Sparse_matrix
     #Compressed_sparse_column_.28CSC_or_CCS.29
   Templates:
     Scalar  type of sparse matrix like double
   Inputs:
     A  sparse m by n matrix
   Outputs:
     num_rows  number of rows
     V  non-zero values, row indices running fastest, size(V) = nnz 
     R  row indices corresponding to vals, size(R) = nnz
     C  index in vals of first entry in each column, size(C) = num_cols+1
  
   All indices and pointers are 0-based
)igl_Qu8mg5v7";

npe_function(harwell_boeing)
npe_doc(ds_harwell_boeing)

npe_arg(a, sparse_double)


npe_begin_code()

  int & num_rows;
  std::vector<Scalar> & v;
  std::vector<Index> & r;
  std::vector<Index> & c;
  igl::harwell_boeing(a, num_rows, v, r, c);
  return std::make_tuple(npe::move(num_rows), npe::move(v), npe::move(r), npe::move(c));

npe_end_code()


