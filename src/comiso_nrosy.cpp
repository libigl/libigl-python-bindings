//TODO: __example
//TODO: linker problem:
/*
ld: warning: direct access in function
'void gmm::copy<gmm::simple_vector_ref<gmm::wsvector<double>*>, gmm::simple_vector_ref<gmm::wsvector<double>*> >(gmm::simple_vector_ref<gmm::wsvector<double>*> const&, gmm::simple_vector_ref<gmm::wsvector<double>*>&)'
 from file 'CMakeFiles/pyigl.dir/comiso_nrosy.out.cpp.o' to global weak symbol 'gmm::warning_level::level(int)::level_' from file
  'CoMISo/libCoMISo.a(MISolver.cc.o)' means the weak symbol cannot be overridden at runtime. This was likely caused by different
  translation units being compiled with different visibility settings.


 */
#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/copyleft/comiso/nrosy.h>

const char* ds_nrosy = R"igl_Qu8mg5v7(
Generate a N-RoSy field from a sparse set of constraints.

Parameters
----------
v : #v by 3 array of mesh vertex coordinates
f : #f by 3 array of mesh faces (must be triangles)
b : #b by 1 array of constrained face indices
bc : #b by 3 array of representative vectors for the constrained faces
b_soft : #s by 1 b for soft constraints
w_soft : #s by 1 weight for the soft constraints (0-1)
bc_soft : #s by 3 bc for soft constraints
n : the degree of the N-RoSy vector field
soft : the strength of the soft constraints w.r.t. smoothness (0 -> smoothness only, 1->constraints only)

Returns
-------
r : #f by 3 the representative vectors of the interpolated field
S : #v by 1 the singularity index for each vertex (0 = regular)

See also
--------
None

Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(nrosy)
npe_doc(ds_nrosy)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_arg(b, npe_matches(f))
npe_arg(bc, npe_matches(v))
npe_arg(b_soft, npe_matches(f))
npe_arg(w_soft, npe_matches(v))
npe_arg(bc_soft, npe_matches(w_soft))
npe_arg(n, int)
npe_arg(soft, double)


npe_begin_code()
  assert_valid_3d_tri_mesh(v, f);
  assert_rows_match(b, bc, "b", "bc");

  assert_rows_match(b_soft, w_soft, "b_soft", "w_soft");
  assert_rows_match(b_soft, bc_soft, "b_soft", "bc_soft");

  // remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::VectorXi b_copy = b.template cast<int>();
  Eigen::MatrixXd bc_copy = bc.template cast<double>();
  Eigen::VectorXi b_soft_copy;
  if (b_soft.size() > 0)
    b_soft_copy = b_soft.template cast<int>();
  Eigen::VectorXd w_soft_copy;
  if (w_soft.size() > 0)
    w_soft_copy = w_soft.template cast<double>();
  Eigen::MatrixXd bc_soft_copy = bc_soft.template cast<double>();
  Eigen::MatrixXd r;
  Eigen::VectorXd s;
  igl::copyleft::comiso::nrosy(v_copy, f_copy, b_copy, bc_copy, b_soft_copy, w_soft_copy, bc_soft_copy, n, soft, r, s);

  EigenDenseLike<npe_Matrix_v> r_row_maj = r.template cast <typename npe_Matrix_v::Scalar>();
  EigenDenseLike<npe_Matrix_v> s_row_maj = s.template cast<typename npe_Matrix_v::Scalar>();
  return std::make_tuple(npe::move(r_row_maj), npe::move(s_row_maj));

npe_end_code()
