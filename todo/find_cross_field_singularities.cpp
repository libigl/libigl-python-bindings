#include <npe.h>
#include <typedefs.h>
#include <igl/find_cross_field_singularities.h>

const char* ds_find_cross_field_singularities = R"igl_Qu8mg5v7(

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
     V                #V by 3 eigen Matrix of mesh vertex 3D positions
     F                #F by 3 eigen Matrix of face (quad) indices
     Handle_MMatch    #F by 3 eigen Matrix containing the integer missmatch of the cross field
                      across all face edges
   Output:
     isSingularity    #V by 1 boolean eigen Vector indicating the presence of a singularity on a vertex
     singularityIndex #V by 1 integer eigen Vector containing the singularity indices
  
)igl_Qu8mg5v7";

npe_function(find_cross_field_singularities)
npe_doc(ds_find_cross_field_singularities)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(handle_m_match, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> is_singularity;
  EigenDense<npe_Scalar_> singularity_index;
  igl::find_cross_field_singularities(v, f, handle_m_match, is_singularity, singularity_index);
  return std::make_tuple(npe::move(is_singularity), npe::move(singularity_index));

npe_end_code()






#include <igl/find_cross_field_singularities.h>

const char* ds_find_cross_field_singularities = R"igl_Qu8mg5v7(

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

 Wrapper that calculates the missmatch if it is not provided.
   Note that the field in PD1 and PD2 MUST BE combed (see igl::comb_cross_field).
   Inputs:
     V                #V by 3 eigen Matrix of mesh vertex 3D positions
     F                #F by 3 eigen Matrix of face (quad) indices
     PD1              #F by 3 eigen Matrix of the first per face cross field vector
     PD2              #F by 3 eigen Matrix of the second per face  cross field vector
   Output:
     isSingularity    #V by 1 boolean eigen Vector indicating the presence of a singularity on a vertex
     singularityIndex #V by 1 integer eigen Vector containing the singularity indices
  
)igl_Qu8mg5v7";

npe_function(find_cross_field_singularities)
npe_doc(ds_find_cross_field_singularities)

npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(pd1, dense_f32, dense_f64)
npe_arg(pd2, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> is_singularity;
  EigenDense<npe_Scalar_> singularity_index;
  bool is_combed;
  igl::find_cross_field_singularities(v, f, pd1, pd2, is_singularity, singularity_index, is_combed);
  return std::make_tuple(npe::move(is_singularity), npe::move(singularity_index), npe::move(is_combed));

npe_end_code()


