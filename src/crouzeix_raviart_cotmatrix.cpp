#include <common.h>
#include <npe.h>
#include <typedefs.h>






#include <igl/crouzeix_raviart_cotmatrix.h>

const char* ds_crouzeix_raviart_cotmatrix = R"igl_Qu8mg5v7(

CROUZEIX_RAVIART_COTMATRIX Compute the Crouzeix-Raviart cotangent
   stiffness matrix.

Parameters
----------
V  #V by dim list of vertex positions
F  #F by 3/4 list of triangle/tetrahedron indices

Returns
-------
L  #E by #E edge/face-based diagonal cotangent matrix
E  #E by 2/3 list of edges/faces
EMAP  #F*3/4 list of indices mapping allE to E

See also
--------
See also: crouzeix_raviart_massmatrix

Notes
-----
None

Examples
--------
See for example "Discrete Quadratic Curvature Energies" [Wardetzky, Bergou,
  Harmon, Zorin, Grinspun 2007]
 
)igl_Qu8mg5v7";

npe_function(crouzeix_raviart_cotmatrix)
npe_doc(ds_crouzeix_raviart_cotmatrix)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()

  assert_valid_tet_or_tri_mesh(v, f);
  EigenSparseLike<npe_Matrix_v> l;
  npe_Matrix_f e;
  npe_Matrix_f emap;
  igl::crouzeix_raviart_cotmatrix(v, f, l, e, emap);
  return std::make_tuple(npe::move(l), npe::move(e), npe::move(emap));

npe_end_code()



const char* ds_crouzeix_raviart_cotmatrix_known_e = R"igl_Qu8mg5v7(
 
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

npe_function(crouzeix_raviart_cotmatrix_known_e)
npe_doc(ds_crouzeix_raviart_cotmatrix_known_e)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(e, npe_matches(f))
npe_arg(emap, npe_matches(f))


npe_begin_code()

  assert_valid_tet_or_tri_mesh(v, f);
  assert_shapes_match(f, emap, "f", "emap");
  EigenSparseLike<npe_Matrix_v> l;
  igl::crouzeix_raviart_cotmatrix(v, f, e, emap, l);
  return npe::move(l);

npe_end_code()


