#include <common.h>
#include <npe.h>
#include <typedefs.h>
#include <igl/copyleft/tetgen/tetrahedralize.h>

const char* ds_tetrahedralize = R"igl_Qu8mg5v7(
Mesh the interior of a surface mesh (V,F) using tetgen.

Parameters
----------
v : #v by 3 vertex position array
f : #v array of polygon face indices into V (0-indexed)
switches : string of tetgen options (See tetgen documentation) e.g.
   "pq1.414a0.01" tries to mesh the interior of a given surface with quality and area constraints. Will mesh the convex hull constrained to pass through V (ignores F)

Returns
-------
tv  #v by 3 vertex position array
tt  #t by 4 array of tet face indices
tf  #f by 3 array of triangle face indices

See also
--------
None

Notes
-----
Returns status:
0 success
1 tetgen threw exception
2 tetgen did not crash but could not create any tets (probably there are
holes, duplicate faces etc.)
-1 other error

Examples
--------

)igl_Qu8mg5v7";


//TODO: libigl matrix to list supports only same type
npe_function(tetrahedralize)
npe_doc(ds_tetrahedralize)
npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long, dense_longlong)
npe_default_arg(switches, std::string, std::string("pYQ"))
npe_begin_code()
   assert_nonzero_rows(v, "v");
   assert_cols_equals(v, 3, "v");
   if(f.rows() > 0){
      assert_cols_equals(f, 3, "f");
   }
  // TODO: remove __copy
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();


  EigenDenseLike<npe_Matrix_v> tv;
  EigenDenseLike<npe_Matrix_f> tt;
  EigenDenseLike<npe_Matrix_f> tf;
  const auto status = igl::copyleft::tetgen::tetrahedralize(v_copy, f_copy, switches, tv, tt, tf);
  return std::make_tuple(status, npe::move(tv), npe::move(tt), npe::move(tf));

  npe_end_code()
