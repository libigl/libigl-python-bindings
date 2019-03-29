#include <npe.h>
#include <typedefs.h>
#include <igl/edge_topology.h>

const char *ds_edge_topology = R"igl_Qu8mg5v7(
Initialize Edges and their topological relations (assumes an edge-manifold mesh)

Parameters
----------
v : #v by dim, list of mesh vertex positions (unused)
f : #f by 3, list of triangle indices into V

Returns
-------
ev : #e by 2, list of edges described as pair of vertices.
fe : #f by 3, list storing triangle-edge relation.
ef : #e by w, list storing edge-triangle relation, uses -1 to indicate boundaries.

See also
--------


Notes
-----
None

Examples
--------
# Mesh in (v, f)
>>> ev, fe, ef = edge_topology(v, f)
)igl_Qu8mg5v7";

npe_function(edge_topology)
npe_doc(ds_edge_topology)
npe_arg(v, dense_f64, dense_f32)
npe_arg(f, dense_i32, dense_i64)
npe_begin_code()

  npe_Matrix_f ev, fe, ef;
  igl::edge_topology(v, f, ev, fe, ef);

return std::make_tuple(npe::move(ev), npe::move(fe), npe::move(ef));

npe_end_code()
