//TODO: __example
// TODO: remove __copy
// copy is necessary since the winding number only supports matrices
#include <npe.h>
#include <typedefs.h>
#include <igl/winding_number.h>

const char *ds_winding_number = R"igl_Qu8mg5v7(
 WINDING_NUMBER Compute the sum of solid angles of a triangle/tetrahedron
   described by points (vectors) V
Parameters
----------
    V  n by 3 list of vertex positions
    F  #F by 3 list of triangle indices, minimum index is 0
    O  no by 3 list of origin positions

Returns
-------
    S  no by 1 list of winding numbers

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(winding_number)
npe_doc(ds_winding_number)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(o, dense_float, dense_double)


npe_begin_code()
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd o_copy = o.template cast<double>();

  Eigen::MatrixXd w;
  igl::winding_number(v_copy, f_copy, o_copy, w);
  return npe::move(w);

npe_end_code()




const char* ds_winding_number1 = R"igl_Qu8mg5v7(
 Compute winding number of a single point

Parameters
----------
    V  n by dim list of vertex positions
    F  #F by dim list of triangle indices, minimum index is 0
    p  single origin position

Returns
-------
  w  winding number of this point

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(winding_number_for_point)
npe_doc(ds_winding_number1)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(p, npe_matches(v))


npe_begin_code()
  Eigen::MatrixXd v_copy = v.template cast<double>();
  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXd p_copy = p.template cast<double>();
  return igl::winding_number(v_copy, f_copy, p_copy);

npe_end_code()


