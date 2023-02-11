#include <common.h>
#include <npe.h>
#include <typedefs.h>

#include <igl/remove_duplicate_vertices.h>


const char* ds_remove_duplicates = R"igl_Qu8mg5v7(

REMOVE_DUPLICATES Remove duplicate vertices upto a uniqueness
  tolerance (epsilon)

Parameters
----------
V  #V by dim list of vertex positions
F  #F by 3 list of triangle indices
epsilon  uniqueness tolerance (significant digit), can probably think of
  this as a tolerance on L1 distance


Returns
-------
SV  #SV by dim new list of vertex positions
SF  #SF by dim new list of faces so SF = F(SVJ,:)

See also
--------
remove_duplicate_vertices

Notes
-----
None

Examples
--------
% Mesh in (V,F)
[SV,SVI, I] = remove_duplicate(V,F,1e-7)

)igl_Qu8mg5v7";

npe_function(remove_duplicates)
npe_doc(ds_remove_duplicates)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(epsilon, double)


npe_begin_code()

  assert_valid_tet_or_tri_mesh_23d(v, f);
  assert_nonzero_rows(v, "v");

  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXd sv;
  EigenDenseLike<npe_Matrix_f> svi, svj, sf;
  igl::remove_duplicate_vertices(v_copy, f, epsilon, sv, svi, svj, sf);
  EigenDenseFloat sv_row_major = sv;

  return std::make_tuple(npe::move(sv_row_major), npe::move(sf));

npe_end_code()


