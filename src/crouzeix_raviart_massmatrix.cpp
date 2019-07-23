// static assertion fail: YOU_MIXED_DIFFERENT_NUMERIC_TYPES__YOU_NEED_TO_USE_THE_CAST_METHOD_OF_MATRIXBASE_TO_CAST_NUMERIC_TYPES_EXPLICITLY

#include <npe.h>
#include <typedefs.h>






#include <igl/crouzeix_raviart_massmatrix.h>

const char* ds_crouzeix_raviart_massmatrix = R"igl_Qu8mg5v7(

CROUZEIX_RAVIART_MASSMATRIX Compute the Crouzeix-Raviart mass matrix where
  M(e,e) is just the sum of the areas of the triangles on either side of an
  edge e.

Parameters
----------
V  #V by dim list of vertex positions
F  #F by 3/4 list of triangle/tetrahedron indices

Returns
-------
M  #E by #E edge/face-based diagonal mass matrix
E  #E by 2/3 list of edges/faces
EMAP  #F*3/4 list of indices mapping allE to E

See also
--------
crouzeix_raviart_cotmatrix

Notes
-----
See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,
  Harmon, Zorin, Grinspun 2007]

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(crouzeix_raviart_massmatrix)
npe_doc(ds_crouzeix_raviart_massmatrix)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenSparseLike<npe_Matrix_v> m;
  npe_Matrix_f e;
  npe_Matrix_f emap;
  igl::crouzeix_raviart_massmatrix(v, f, m, e, emap);
  return std::make_tuple(npe::move(m), npe::move(e), npe::move(emap));

npe_end_code()



const char* ds_crouzeix_raviart_massmatrix_known_e = R"igl_Qu8mg5v7(

wrapper if E and EMAP are already computed (better match!)

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

)igl_Qu8mg5v7";

npe_function(crouzeix_raviart_massmatrix_known_e)
npe_doc(ds_crouzeix_raviart_massmatrix_known_e)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(e, npe_matches(f))
npe_arg(emap, npe_matches(f))


npe_begin_code()

  EigenSparseLike<npe_Matrix_v> m;
  igl::crouzeix_raviart_massmatrix(v, f, e, emap, m);
  return npe::move(m);

npe_end_code()


