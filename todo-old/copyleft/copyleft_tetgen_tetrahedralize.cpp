#include <npe.h>
#include <typedefs.h>






#include <igl/tetrahedralize.h>

const char* ds_tetrahedralize = R"igl_Qu8mg5v7(

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

 Mesh the interior of a surface mesh (V,F) using tetgen
      
       Inputs:
         V  #V by 3 vertex position list
         F  #F list of polygon face indices into V (0-indexed)
         switches  string of tetgen options (See tetgen documentation) e.g.
           "pq1.414a0.01" tries to mesh the interior of a given surface with
             quality and area constraints
           "" will mesh the convex hull constrained to pass through V (ignores F)
       Outputs:
         TV  #V by 3 vertex position list
         TT  #T by 4 list of tet face indices
         TF  #F by 3 list of triangle face indices
       Returns status:
         0 success
         1 tetgen threw exception
         2 tetgen did not crash but could not create any tets (probably there are
           holes, duplicate faces etc.)
         -1 other error
)igl_Qu8mg5v7";

npe_function(tetrahedralize)
npe_doc(ds_tetrahedralize)

npe_arg(v, int &)
npe_arg(f, int &)
npe_arg(switches, std::string)


npe_begin_code()

  int & tv;
  int & tt;
  int & tf;
  igl::  copyleft::  tetgen::tetrahedralize(v, f, switches, tv, tt, tf);
  return std::make_tuple(npe::move(tv), npe::move(tt), npe::move(tf));

npe_end_code()
#include <igl/tetrahedralize.h>

const char* ds_tetrahedralize = R"igl_Qu8mg5v7(

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

 Wrapper with Eigen types
       Templates:
         DerivedV  real-value: i.e. from MatrixXd
         DerivedF  integer-value: i.e. from MatrixXi
)igl_Qu8mg5v7";

npe_function(tetrahedralize)
npe_doc(ds_tetrahedralize)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(switches, std::string)


npe_begin_code()

  EigenDense<npe_Scalar_> tv;
  EigenDense<npe_Scalar_> tt;
  EigenDense<npe_Scalar_> tf;
  igl::  copyleft::  tetgen::tetrahedralize(v, f, switches, tv, tt, tf);
  return std::make_tuple(npe::move(tv), npe::move(tt), npe::move(tf));

npe_end_code()
#include <igl/tetrahedralize.h>

const char* ds_tetrahedralize = R"igl_Qu8mg5v7(

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

 Mesh the interior of a surface mesh (V,F) using tetgen
      
       Inputs:
         V  #V by 3 vertex position list
         F  #F list of polygon face indices into V (0-indexed)
			   M  #V list of markers for vertices
         switches  string of tetgen options (See tetgen documentation) e.g.
           "pq1.414a0.01" tries to mesh the interior of a given surface with
             quality and area constraints
           "" will mesh the convex hull constrained to pass through V (ignores F)
       Outputs:
         TV  #V by 3 vertex position list
         TT  #T by 4 list of tet face indices
         TF  #F by 3 list of triangle face indices
			   TM  #V list of markers for vertices
       Returns status:
         0 success
         1 tetgen threw exception
         2 tetgen did not crash but could not create any tets (probably there are
           holes, duplicate faces etc.)
         -1 other error
)igl_Qu8mg5v7";

npe_function(tetrahedralize)
npe_doc(ds_tetrahedralize)

npe_arg(v, int &)
npe_arg(f, int &)
npe_arg(vm, int &)
npe_arg(fm, int &)
npe_arg(switches, std::string)


npe_begin_code()

  int & tv;
  int & tt;
  int & tf;
  int & tm;
  igl::  copyleft::  tetgen::tetrahedralize(v, f, vm, fm, switches, tv, tt, tf, tm);
  return std::make_tuple(npe::move(tv), npe::move(tt), npe::move(tf), npe::move(tm));

npe_end_code()
#include <igl/tetrahedralize.h>

const char* ds_tetrahedralize = R"igl_Qu8mg5v7(

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

 Wrapper with Eigen types
       Templates:
         DerivedV  real-value: i.e. from MatrixXd
         DerivedF  integer-value: i.e. from MatrixXi
)igl_Qu8mg5v7";

npe_function(tetrahedralize)
npe_doc(ds_tetrahedralize)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(vm, dense_float, dense_double)
npe_arg(fm, dense_float, dense_double)
npe_arg(switches, std::string)


npe_begin_code()

  EigenDense<npe_Scalar_> tv;
  EigenDense<npe_Scalar_> tt;
  EigenDense<npe_Scalar_> tf;
  EigenDense<npe_Scalar_> tm;
  igl::  copyleft::  tetgen::tetrahedralize(v, f, vm, fm, switches, tv, tt, tf, tm);
  return std::make_tuple(npe::move(tv), npe::move(tt), npe::move(tf), npe::move(tm));

npe_end_code()


