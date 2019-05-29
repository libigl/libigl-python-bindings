#include <npe.h>
#include <typedefs.h>
#include <igl/harmonic.h>

//TODO: is is only dense_int because min_quad_with_fixed_data hardcodes int, fixme

const char* ds_harmonic_w = R"igl_Qu8mg5v7(
Compute k-harmonic weight functions "coordinates".

Parameters
----------
     V  #V by dim vertex positions
     F  #F by simplex-size list of element indices
     b  #b boundary indices into V
     bc #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
    W  #V by #W list of weights

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic_weights)
npe_doc(ds_harmonic_w)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_longlong)
npe_arg(b, dense_int)
npe_arg(bc, npe_matches(v))
npe_arg(k, int)

npe_begin_code()

  EigenDenseLike<npe_Matrix_v> w;
  igl::harmonic(v, f, b, bc, k, w);
  return npe::move(w);

npe_end_code()
#include <igl/harmonic.h>


const char* ds_harmonic_ul = R"igl_Qu8mg5v7(

Compute harmonic map using uniform laplacian operator

Parameters
----------
     F  #F by simplex-size list of element indices
     b  #b boundary indices into V
     bc #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
    W  #V by #W list of weights

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic_uniform_laplacian)
npe_doc(ds_harmonic_ul)

npe_arg(f, dense_int, dense_longlong)
npe_arg(b, dense_int)
npe_arg(bc, dense_float, dense_double)
npe_arg(k, int)


npe_begin_code()

  EigenDenseLike<npe_Matrix_bc> w;
  igl::harmonic(f, b, bc, k, w);
  return npe::move(w);

npe_end_code()






#include <igl/harmonic.h>

const char* ds_harmonic = R"igl_Qu8mg5v7(

Compute a harmonic map using a given Laplacian and mass matrix

Parameters
----------
     L  #V by #V discrete (integrated) Laplacian
     M  #V by #V mass matrix
     b  #b boundary indices into V
     bc  #b by #W list of boundary values
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
  W  #V by #V list of weights

See also
--------


Notes
-----

Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic)
npe_doc(ds_harmonic)
//TODO: l and bc need to have same type, matching missing
npe_arg(l, sparse_float)
npe_arg(m, npe_matches(l))
npe_arg(b, dense_int)
npe_arg(bc, dense_float)
npe_arg(k, int)


npe_begin_code()

  EigenDenseLike<npe_Matrix_bc> w;
  igl::harmonic(l, m, b, bc, k, w);
  return npe::move(w);

npe_end_code()
#include <igl/harmonic.h>

const char* ds_harmonic_int_lapl = R"igl_Qu8mg5v7(

 Build the discrete k-harmonic operator (computing integrated quantities).
   That is, if the k-harmonic PDE is Q x = 0, then this minimizes x' Q x


Parameters
----------
     L  #V by #V discrete (integrated) Laplacian
     M  #V by #V mass matrix
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
    Q  #V by #V discrete (integrated) k-Laplacian
See also
--------


Notes
-----
Examples
--------

)igl_Qu8mg5v7";

npe_function(harmonic_integrated_with_laplacian)
npe_doc(ds_harmonic_int_lapl)

npe_arg(l, sparse_float, sparse_double)
npe_arg(m, npe_matches(l))
npe_arg(k, int)


npe_begin_code()
  EigenSparseLike<npe_Matrix_l> q;
  igl::harmonic(l, m, k, q);
  return npe::move(q);

npe_end_code()
#include <igl/harmonic.h>

const char* ds_harmonic_int = R"igl_Qu8mg5v7(

Parameters
----------
   V  #V by dim vertex positions
     F  #F by simplex-size list of element indices
     k  power of harmonic operation (1: harmonic, 2: biharmonic, etc)

Returns
-------
    Q  #V by #V discrete (integrated) k-Laplacian

See also
--------


Notes
-----


Examples
--------


)igl_Qu8mg5v7";

npe_function(_integrated)
npe_doc(ds_harmonic_int)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_longlong)
npe_arg(k, int)


npe_begin_code()

  EigenSparseLike<npe_Matrix_v> q;
  igl::harmonic(v, f, k, q);
  return npe::move(q);

npe_end_code()


