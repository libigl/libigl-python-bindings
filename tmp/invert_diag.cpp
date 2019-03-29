#include <tuple>
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <npe.h>
#include <typedefs.h>

#include <igl/invert_diag.h>


npe_function(invert_diag)
npe_arg(x, sparse_f64, sparse_f32) //TODO Check if can remove this function

npe_begin_code()
using namespace std;

npe_Matrix_x y;
igl::invert_diag(x, y);
return npe::move(y);

npe_end_code()


