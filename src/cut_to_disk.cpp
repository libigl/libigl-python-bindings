#include <npe.h>
#include <common.h>
#include <typedefs.h>
#include <igl/cut_to_disk.h>

const char *ds_cut_to_disk = R"igl_Qu8mg5v7(

Given a triangle mesh, computes a set of edge cuts sufficient to carve the
mesh into a topological disk, without disconnecting any connected components.
Nothing else about the cuts (including number, total length, or smoothness)
is guaranteed to be optimal.

Simply-connected components without boundary (topological spheres) are left
untouched (delete any edge if you really want a disk).
All other connected components are cut into disks. Meshes with boundary are
supported; boundary edges will be included as cuts.

The cut mesh itself can be materialized using cut_mesh().

Implements the triangle-deletion approach described by Gu et al's
"Geometry Images."

Parameters
----------

F  #F by 3 list of the faces (must be triangles)

Returns
-------

cuts  List of cuts. Each cut is a sequence of vertex indices (where
       pairs of consecutive vertices share a face), is simple, and is either
       a closed loop (in which the first and last indices are identical) or
       an open curve. Cuts are edge-disjoint.

See also
--------


Notes
-----
None

Examples
--------


)igl_Qu8mg5v7";

npe_function(cut_to_disk)
npe_doc(ds_cut_to_disk)

npe_arg(f, dense_int, dense_long, dense_longlong)


npe_begin_code()
  assert_valid_tri_mesh_faces(f);

  std::vector<std::vector<int> > cuts;
  igl::cut_to_disk(f, cuts);
  return cuts;

npe_end_code()
