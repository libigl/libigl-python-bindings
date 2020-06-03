#include <npe.h>
#include <typedefs.h>






#include <igl/unique_rows.h>

const char* ds_unique_rows = R"igl_Qu8mg5v7(

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

 Act like matlab's [C,IA,IC] = unique(X,'rows')
  
   Templates:
     DerivedA derived scalar type, e.g. MatrixXi or MatrixXd
     DerivedIA derived integer type, e.g. MatrixXi
     DerivedIC derived integer type, e.g. MatrixXi
   Inputs:
     A  m by n matrix whose entries are to unique'd according to rows
   Outputs:
     C  #C vector of unique rows in A
     IA  #C index vector so that C = A(IA,:);
     IC  #A index vector so that A = C(IC,:);
)igl_Qu8mg5v7";

npe_function(unique_rows)
npe_doc(ds_unique_rows)

npe_arg(a, Eigen::DenseBase<DerivedA> &)


npe_begin_code()

  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> ia;
  EigenDense<npe_Scalar_> ic;
  igl::unique_rows(a, c, ia, ic);
  return std::make_tuple(npe::move(c), npe::move(ia), npe::move(ic));

npe_end_code()


