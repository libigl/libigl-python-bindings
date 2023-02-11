#include <common.h>
#include <npe.h>
#include <typedefs.h>

#include <igl/edge_flaps.h>

const char *ds_edge_flaps = R"igl_Qu8mg5v7(

Determine "edge flaps": two faces on either side of a unique edge (assumes edge-manifold mesh)


Parameters
----------

F  #F by 3 list of face indices

Returns
-------

E  #E by 2 list of edge indices into V.
EMAP #F*3 list of indices into E, mapping each directed edge to unique
  unique edge in E
EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
  F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
  e=(j->i)
EI  #E by 2 list of edge flap corners (see above).

See also
--------


Notes
-----
None

Examples
--------

)igl_Qu8mg5v7";

npe_function(edge_flaps)
npe_doc(ds_edge_flaps)

npe_arg(f, dense_int, dense_long)


npe_begin_code()
  assert_valid_tri_mesh_faces(f);

  Eigen::MatrixXi f_copy = f.template cast<int>();
  Eigen::MatrixXi e_copy;
  Eigen::VectorXi emap_copy;
  Eigen::MatrixXi ef_copy;
  Eigen::MatrixXi ei_copy;
  igl::edge_flaps(f_copy, e_copy, emap_copy, ef_copy, ei_copy);

  EigenDense<npe_Scalar_f> e = e_copy.template cast<npe_Scalar_f>();
  EigenDense<npe_Scalar_f> emap = emap_copy.template cast<npe_Scalar_f>();
  EigenDense<npe_Scalar_f> ef = ef_copy.template cast<npe_Scalar_f>();
  EigenDense<npe_Scalar_f> ei = ei_copy.template cast<npe_Scalar_f>();
  return std::make_tuple(npe::move(e), npe::move(emap), npe::move(ef), npe::move(ei));

npe_end_code()


