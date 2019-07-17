// TODO: __example, decide if to remove the first function

#include <npe.h>
#include <typedefs.h>
#include <igl/is_edge_manifold.h>



const char* ds_is_edge_manifold = R"igl_Qu8mg5v7(
See is_edge_manifold for the documentation.
)igl_Qu8mg5v7";

npe_function(is_edge_manifold)
npe_doc(ds_is_edge_manifold)

npe_arg(f, dense_int, dense_long)


npe_begin_code()

  return igl::is_edge_manifold(f);

npe_end_code()


