#include <npe.h>
#include <igl/adjacency_list.h>
#include <pybind11/stl.h>

const char* ds_adjacency_list = R"igl_Qu8mg5v7(

Constructs the graph adjacency list of a given mesh (v, f)

Parameters
----------
f : #f by dim array of fixed dimensional (e.g. triangle (#f by 3),
    tet (#f by 4), quad (#f by 4), etc...) mesh faces

Returns
-------
list of lists containing at index i the adjacent vertices of vertex i

See also
--------
adjacency_matrix

Notes
-----

Examples
--------
# Mesh in (v, f)
>>> a = mesh_adjacency_list(f)
)igl_Qu8mg5v7";

npe_function(adjacency_list)
npe_doc(ds_adjacency_list)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  std::vector<std::vector<npe_Scalar_f>> a;
  igl::adjacency_list(f, a);
  return pybind11::detail::type_caster<decltype(a)>::cast(a, pybind11::return_value_policy::move, pybind11::none());

npe_end_code()
