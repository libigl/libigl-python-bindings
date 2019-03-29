#include <npe.h>
#include <typedefs.h>
#include <igl/arap_rhs.h>

const char* ds_arap_rhs = R"igl_Qu8mg5v7(
Guild right-hand side constructor of global poisson solve for various ARAP energies
  Inputs:

  Outputs:
    K  #V*dim by #(F|V)*dim*dim matrix such that:
      b = K * reshape(permute(R,[3 1 2]),size(V|F,1)*size(V,2)*size(V,2),1);

Parameters
----------
v : #v by Vdim list of initial domain positions
f : #f by 3 list of triangle indices into v
d : dimension being used at solve time. For deformation usually dim = V.cols(), for surface parameterization V.cols() = 3 and dim = 2
energy : ARAPEnergyType enum value defining which energy is being used. See igl.ARAPEnergyType for valid options and explanations.

Returns
-------
#v*d by #(f|v)*dim*dim matrix such that: b = K * reshape(permute(R,[3 1 2]),size(V|F,1)*size(V,2)*size(V,2),1);

See also
--------
arap_linear_block, arap

Notes
-----

Examples
--------
)igl_Qu8mg5v7";

npe_function(arap_rhs)
npe_doc(ds_arap_rhs)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32)
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
  } else if (energy == igl::ARAP_ENERGY_TYPE_DEFAULT) {
    // FIXME: arap_rhs should pick a default but it doesn't
    std::string errmsg =
        std::string("Invalid enum for energy type should be in the range 0 to ") +
        std::to_string(igl::ARAP_ENERGY_TYPE_DEFAULT-1);
  }

  EigenSparseLike<npe_Matrix_v> k;
  igl::arap_rhs(v, f, d, igl::ARAPEnergyType(energy), k);
  return npe::move(k);

npe_end_code()


