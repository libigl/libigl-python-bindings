#include <npe.h>
#include <string>
#include <typedefs.h>
#include <igl/arap_linear_block.h>

const char* ds_arap_linear_block = R"igl_Qu8mg5v7(
Constructs a block of the matrix which constructs the
linear terms of a given arap energy. When treating rotations as knowns
(arranged in a column), then this constructs Kd of K such that the linear
portion of the energy is as a column:
 K * R = [Kx Z  ... Ky Z  ...
          Z  Kx ... Z  Ky ...
          ... ]
These blocks are also used to build the "covariance scatter matrices".
Here we want to build a scatter matrix that multiplies against positions
(treated as known) producing covariance matrices to fit each rotation.
Notice that in the case of the RHS of the poisson solve the rotations are
known and the positions unknown, and vice versa for rotation fitting.
These linear block just relate the rotations to the positions, linearly in
each.


Parameters
----------
v : #v by dim list of initial domain positions
f : #f by #simplex size list of triangle indices into V
d : coordinate of linear constructor to build

Returns
-------
#v by #v/#f block of the linear constructor matrix corresponding to coordinate d

See also
--------
arap, arap_dof

Notes
-----

Examples
--------

)igl_Qu8mg5v7";

/*
 * arap_linear_block
 */
npe_function(arap_linear_block)
npe_doc(ds_arap_linear_block)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(d, int)
npe_arg(energy, int)
npe_begin_code()

  static_assert(int(igl::ARAPEnergyType::ARAP_ENERGY_TYPE_SPOKES) == 0, "ARAPEnergyType enum changed!");
  static_assert(int(igl::ARAPEnergyType::ARAP_ENERGY_TYPE_SPOKES_AND_RIMS) == 1, "ARAPEnergyType enum changed!");
  static_assert(int(igl::ARAPEnergyType::ARAP_ENERGY_TYPE_ELEMENTS) == 2, "ARAPEnergyType enum changed!");
  static_assert(int(igl::ARAPEnergyType::ARAP_ENERGY_TYPE_DEFAULT) == 3, "ARAPEnergyType enum changed!");
  static_assert(int(igl::ARAPEnergyType::NUM_ARAP_ENERGY_TYPES) == 4, "ARAPEnergyType enum changed!");

  if (energy >= igl::NUM_ARAP_ENERGY_TYPES) {
    std::string errmsg =
        std::string("Invalid enum for energy type should be in the range 0 to ") +
        std::to_string(igl::NUM_ARAP_ENERGY_TYPES-1);
    throw pybind11::value_error(errmsg);
  }

  EigenSparseLike<npe_Matrix_v> kd;
  igl::arap_linear_block(v, f, d, igl::ARAPEnergyType(energy), kd);
  return npe::move(kd);

npe_end_code()




/*
 * arap_linear_block_spokes
 */
npe_function(arap_linear_block_spokes)
npe_doc(ds_arap_linear_block)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(d, int)
npe_begin_code()

  EigenSparseLike<npe_Matrix_v> kd;
  igl::arap_linear_block_spokes(v, f, d, kd);
  return npe::move(kd);

npe_end_code()



/*
 * arap_linear_block_spokes_and_rims
 */
npe_function(arap_linear_block_spokes_and_rims)
npe_doc(ds_arap_linear_block)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(d, int)
npe_begin_code()

  EigenSparseLike<npe_Matrix_v> kd;
  igl::arap_linear_block_spokes_and_rims(v, f, d, kd);
  return npe::move(kd);

npe_end_code()




/*
 * arap_linear_block_spokes_and_rims
 */
npe_function(arap_linear_block_elements)
npe_doc(ds_arap_linear_block)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)
npe_arg(d, int)
npe_begin_code()

  EigenSparseLike<npe_Matrix_v> kd;
  igl::arap_linear_block_elements(v, f, d, kd);
  return npe::move(kd);

npe_end_code()
