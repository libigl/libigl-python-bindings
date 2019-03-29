#include <npe.h>
#include <typedefs.h>
#include <igl/harmonic.h>

const char* ds_harmonic = R"igl_Qu8mg5v7(

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

 Compute k-harmonic weight functions "coordinates".
  
  
   Inputs:
     V  #V by dim vertex positions
     F  #F by simplex-size list of element indices
     b  #b boundary indices into V
     bc #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)
   Outputs:
     W  #V by #W list of weights
  
)igl_Qu8mg5v7";

npe_function(harmonic)
npe_doc(ds_harmonic)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(b, dense_f32, dense_f64)
npe_arg(bc, dense_f32, dense_f64)
npe_arg(k, int)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::harmonic(v, f, b, bc, k, w);
  return npe::move(w);

npe_end_code()
#include <igl/harmonic.h>

const char* ds_harmonic = R"igl_Qu8mg5v7(

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

 Compute harmonic map using uniform laplacian operator
  
   Inputs:
     F  #F by simplex-size list of element indices
     b  #b boundary indices into V
     bc #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)
   Outputs:
     W  #V by #W list of weights
  
)igl_Qu8mg5v7";

npe_function(harmonic)
npe_doc(ds_harmonic)

npe_arg(f, dense_i32, dense_i64)
npe_arg(b, dense_f32, dense_f64)
npe_arg(bc, dense_f32, dense_f64)
npe_arg(k, int)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::harmonic(f, b, bc, k, w);
  return npe::move(w);

npe_end_code()






#include <igl/harmonic.h>

const char* ds_harmonic = R"igl_Qu8mg5v7(

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

 Compute a harmonic map using a given Laplacian and mass matrix
  
   Inputs:
     L  #V by #V discrete (integrated) Laplacian  
     M  #V by #V mass matrix
     b  #b boundary indices into V
     bc  #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)
   Outputs:
     W  #V by #V list of weights
)igl_Qu8mg5v7";

npe_function(harmonic)
npe_doc(ds_harmonic)

npe_arg(l, Eigen::SparseMatrix<DerivedL> &)
npe_arg(m, Eigen::SparseMatrix<DerivedM> &)
npe_arg(b, dense_f32, dense_f64)
npe_arg(bc, dense_f32, dense_f64)
npe_arg(k, int)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::harmonic(l, m, b, bc, k, w);
  return npe::move(w);

npe_end_code()
#include <igl/harmonic.h>

const char* ds_harmonic = R"igl_Qu8mg5v7(

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

 Build the discrete k-harmonic operator (computing integrated quantities).
   That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x
  
   Inputs:
     L  #V by #V discrete (integrated) Laplacian  
     M  #V by #V mass matrix
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)
   Outputs:
     Q  #V by #V discrete (integrated) k-Laplacian  
)igl_Qu8mg5v7";

npe_function(harmonic)
npe_doc(ds_harmonic)

npe_arg(l, Eigen::SparseMatrix<DerivedL> &)
npe_arg(m, Eigen::SparseMatrix<DerivedM> &)
npe_arg(k, int)


npe_begin_code()

  Eigen::SparseMatrix<DerivedQ> & q;
  igl::harmonic(l, m, k, q);
  return npe::move(q);

npe_end_code()
#include <igl/harmonic.h>

const char* ds_harmonic = R"igl_Qu8mg5v7(

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

 Inputs:
     V  #V by dim vertex positions
     F  #F by simplex-size list of element indices
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)
   Outputs:
     Q  #V by #V discrete (integrated) k-Laplacian  
)igl_Qu8mg5v7";

npe_function(harmonic)
npe_doc(ds_harmonic)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(k, int)


npe_begin_code()

  Eigen::SparseMatrix<DerivedQ> & q;
  igl::harmonic(v, f, k, q);
  return npe::move(q);

npe_end_code()


