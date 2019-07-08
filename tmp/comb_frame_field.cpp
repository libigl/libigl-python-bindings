// TODO: Maybe need more templates or wasy to wrap around output params
//        deduced conflicting types or param ... Eigen::Map<Eigen::Matrix<...>>
//        and Eigen::Matrix<...>

#include <npe.h>
#include <typedefs.h>
#include <igl/comb_frame_field.h>

const char* ds_comb_frame_field = R"igl_Qu8mg5v7(

Parameters
----------
V            #V by 3 eigen Matrix of mesh vertex 3D positions
F            #F by 4 eigen Matrix of face (quad) indices
PD1          #F by 3 eigen Matrix of the first per face cross field vector
PD2          #F by 3 eigen Matrix of the second per face cross field vector
BIS1_combed  #F by 3 eigen Matrix of the first combed bisector field vector
BIS2_combed  #F by 3 eigen Matrix of the second combed bisector field vector

Returns
-------
PD1_combed  #F by 3 eigen Matrix of the first combed cross field vector
PD2_combed  #F by 3 eigen Matrix of the second combed cross field vector

See also
--------


Notes
-----
None

Examples
--------

  
)igl_Qu8mg5v7";

npe_function(comb_frame_field)
npe_doc(ds_comb_frame_field)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(pd1, dense_float, dense_double)
npe_arg(pd2, npe_matches(pd1))
npe_arg(bis1_combed, npe_matches(pd1))
npe_arg(bis2_combed, npe_matches(pd1))


npe_begin_code()

  npe_Matrix_pd1 pd1_combed;
  npe_Matrix_pd1 pd2_combed;
  igl::comb_frame_field(v, f, pd1, pd2, bis1_combed, bis2_combed, pd1_combed, pd2_combed);
  return std::make_tuple(npe::move(pd1_combed), npe::move(pd2_combed));

npe_end_code()


