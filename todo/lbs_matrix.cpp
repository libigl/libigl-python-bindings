#include <npe.h>
#include <typedefs.h>






#include <igl/lbs_matrix.h>

const char* ds_lbs_matrix = R"igl_Qu8mg5v7(

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

 LBS_MATRIX Linear blend skinning can be expressed by V' = M * T where V' is
   a #V by dim matrix of deformed vertex positions (one vertex per row), M is a
   #V by (dim+1)*#T (composed of weights and rest positions) and T is a
   #T*(dim+1) by dim matrix of #T stacked transposed transformation matrices.
   See equations (1) and (2) in "Fast Automatic Skinning Transformations"
   [Jacobson et al 2012]
  
   Inputs:
     V  #V by dim list of rest positions
     W  #V+ by #T  list of weights
   Outputs:
     M  #V by #T*(dim+1)
  
   In MATLAB:
     kron(ones(1,size(W,2)),[V ones(size(V,1),1)]).*kron(W,ones(1,size(V,2)+1))
)igl_Qu8mg5v7";

npe_function(lbs_matrix)
npe_doc(ds_lbs_matrix)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(w, Eigen::MatrixXd &)


npe_begin_code()

  Eigen::MatrixXd & m;
  igl::lbs_matrix(v, w, m);
  return npe::move(m);

npe_end_code()
#include <igl/lbs_matrix_column.h>

const char* ds_lbs_matrix_column = R"igl_Qu8mg5v7(

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

 LBS_MATRIX  construct a matrix that when multiplied against a column of
   affine transformation entries computes new coordinates of the vertices
  
   I'm not sure it makes since that the result is stored as a sparse matrix.
   The number of non-zeros per row *is* dependent on the number of mesh
   vertices and handles.
  
   Inputs:
     V  #V by dim list of vertex rest positions
     W  #V by #handles list of correspondence weights
   Output:
     M  #V * dim by #handles * dim * (dim+1) matrix such that
       new_V(:) = LBS(V,W,A) = reshape(M * A,size(V)), where A is a column
       vectors formed by the entries in each handle's dim by dim+1 
       transformation matrix. Specifcally, A =
         reshape(permute(Astack,[3 1 2]),n*dim*(dim+1),1)
       or A = [Lxx;Lyx;Lxy;Lyy;tx;ty], and likewise for other dim
       if Astack(:,:,i) is the dim by (dim+1) transformation at handle i
)igl_Qu8mg5v7";

npe_function(lbs_matrix_column)
npe_doc(ds_lbs_matrix_column)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(w, Eigen::MatrixXd &)


npe_begin_code()

  Eigen::SparseMatrix<double> & m;
  igl::lbs_matrix_column(v, w, m);
  return npe::move(m);

npe_end_code()
#include <igl/lbs_matrix_column.h>

const char* ds_lbs_matrix_column = R"igl_Qu8mg5v7(
See lbs_matrix_column for the documentation.
)igl_Qu8mg5v7";

npe_function(lbs_matrix_column)
npe_doc(ds_lbs_matrix_column)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(w, Eigen::MatrixXd &)


npe_begin_code()

  Eigen::MatrixXd & m;
  igl::lbs_matrix_column(v, w, m);
  return npe::move(m);

npe_end_code()
#include <igl/lbs_matrix_column.h>

const char* ds_lbs_matrix_column = R"igl_Qu8mg5v7(

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

 Same as LBS_MATRIX above but instead of giving W as a full matrix of weights
   (each vertex has #handles weights), a constant number of weights are given
   for each vertex.
   
   Inputs:
     V  #V by dim list of vertex rest positions
     W  #V by k  list of k correspondence weights per vertex
     WI  #V by k  list of k correspondence weight indices per vertex. Such that
       W(j,WI(i)) gives the ith most significant correspondence weight on vertex j
   Output:
     M  #V * dim by #handles * dim * (dim+1) matrix such that
       new_V(:) = LBS(V,W,A) = reshape(M * A,size(V)), where A is a column
       vectors formed by the entries in each handle's dim by dim+1 
       transformation matrix. Specifcally, A =
         reshape(permute(Astack,[3 1 2]),n*dim*(dim+1),1)
       or A = [Lxx;Lyx;Lxy;Lyy;tx;ty], and likewise for other dim
       if Astack(:,:,i) is the dim by (dim+1) transformation at handle i
  
)igl_Qu8mg5v7";

npe_function(lbs_matrix_column)
npe_doc(ds_lbs_matrix_column)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(w, Eigen::MatrixXd &)
npe_arg(wi, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::SparseMatrix<double> & m;
  igl::lbs_matrix_column(v, w, wi, m);
  return npe::move(m);

npe_end_code()
#include <igl/lbs_matrix_column.h>

const char* ds_lbs_matrix_column = R"igl_Qu8mg5v7(
See lbs_matrix_column for the documentation.
)igl_Qu8mg5v7";

npe_function(lbs_matrix_column)
npe_doc(ds_lbs_matrix_column)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(w, Eigen::MatrixXd &)
npe_arg(wi, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::MatrixXd & m;
  igl::lbs_matrix_column(v, w, wi, m);
  return npe::move(m);

npe_end_code()


