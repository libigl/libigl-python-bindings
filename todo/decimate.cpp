#include <npe.h>
#include <typedefs.h>






#include <igl/decimate.h>

const char* ds_decimate = R"igl_Qu8mg5v7(

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

 Assumes (V,F) is a manifold mesh (possibly with boundary) Collapses edges
   until desired number of faces is achieved. This uses default edge cost and
   merged vertex placement functions {edge length, edge midpoint}.
  
   Inputs:
     V  #V by dim list of vertex positions
     F  #F by 3 list of face indices into V.
     max_m  desired number of output faces
   Outputs:
     U  #U by dim list of output vertex posistions (can be same ref as V)
     G  #G by 3 list of output face indices into U (can be same ref as G)
     J  #G list of indices into F of birth face
     I  #U list of indices into V of birth vertices
   Returns true if m was reached (otherwise #G > m)
)igl_Qu8mg5v7";

npe_function(decimate)
npe_doc(ds_decimate)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(max_m, size_t)


npe_begin_code()

  Eigen::MatrixXd & u;
  Eigen::MatrixXi & g;
  Eigen::VectorXi & j;
  Eigen::VectorXi & i;
  igl::decimate(v, f, max_m, u, g, j, i);
  return std::make_tuple(npe::move(u), npe::move(g), npe::move(j), npe::move(i));

npe_end_code()
#include <igl/decimate.h>

const char* ds_decimate = R"igl_Qu8mg5v7(

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
     V  #V by dim list of vertex positions
     F  #F by 3 list of face indices into V.
     max_m  desired number of output faces
   Outputs:
     U  #U by dim list of output vertex posistions (can be same ref as V)
     G  #G by 3 list of output face indices into U (can be same ref as G)
     J  #G list of indices into F of birth face
   Returns true if m was reached (otherwise #G > m)
)igl_Qu8mg5v7";

npe_function(decimate)
npe_doc(ds_decimate)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(max_m, size_t)


npe_begin_code()

  Eigen::MatrixXd & u;
  Eigen::MatrixXi & g;
  Eigen::VectorXi & j;
  igl::decimate(v, f, max_m, u, g, j);
  return std::make_tuple(npe::move(u), npe::move(g), npe::move(j));

npe_end_code()
#include <igl/decimate.h>

const char* ds_decimate = R"igl_Qu8mg5v7(

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

 Assumes a **closed** manifold mesh. See igl::connect_boundary_to_infinity
   and igl::decimate in decimate.cpp
   is handling meshes with boundary by connecting all boundary edges with
   dummy facets to infinity **and** modifying the stopping criteria.
  
   Inputs:
     cost_and_placement  function computing cost of collapsing an edge and 3d
       position where it should be placed:
       cost_and_placement(V,F,E,EMAP,EF,EI,cost,placement);
     stopping_condition  function returning whether to stop collapsing edges
       based on current state. Guaranteed to be called after _successfully_
       collapsing edge e removing edges (e,e1,e2) and faces (f1,f2):
       bool should_stop =
         stopping_condition(V,F,E,EMAP,EF,EI,Q,Qit,C,e,e1,e2,f1,f2);
)igl_Qu8mg5v7";

npe_function(decimate)
npe_doc(ds_decimate)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(cost_and_placement, std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> &)
npe_arg(stopping_condition, std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int)> &)


npe_begin_code()

  Eigen::MatrixXd & u;
  Eigen::MatrixXi & g;
  Eigen::VectorXi & j;
  Eigen::VectorXi & i;
  igl::decimate(v, f, cost_and_placement, stopping_condition, u, g, j, i);
  return std::make_tuple(npe::move(u), npe::move(g), npe::move(j), npe::move(i));

npe_end_code()
#include <igl/decimate.h>

const char* ds_decimate = R"igl_Qu8mg5v7(

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
     pre_collapse  callback called with index of edge whose collapse is about
       to be attempted (see collapse_edge)
     post_collapse  callback called with index of edge whose collapse was
       just attempted and a flag revealing whether this was successful (see
       collapse_edge)
)igl_Qu8mg5v7";

npe_function(decimate)
npe_doc(ds_decimate)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(cost_and_placement, std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> &)
npe_arg(stopping_condition, std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int)> &)
npe_arg(pre_collapse, std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int)> &)
npe_arg(post_collapse, std::function<void (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int, const bool)> &)


npe_begin_code()

  Eigen::MatrixXd & u;
  Eigen::MatrixXi & g;
  Eigen::VectorXi & j;
  Eigen::VectorXi & i;
  igl::decimate(v, f, cost_and_placement, stopping_condition, pre_collapse, post_collapse, u, g, j, i);
  return std::make_tuple(npe::move(u), npe::move(g), npe::move(j), npe::move(i));

npe_end_code()
#include <igl/decimate.h>

const char* ds_decimate = R"igl_Qu8mg5v7(

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
     EMAP #F*3 list of indices into E, mapping each directed edge to unique
       unique edge in E
     EF  #E by 2 list of edge flaps, EF(e,0)=f means e=(i-->j) is the edge of
       F(f,:) opposite the vth corner, where EI(e,0)=v. Similarly EF(e,1) "
       e=(j->i)
     EI  #E by 2 list of edge flap corners (see above).
)igl_Qu8mg5v7";

npe_function(decimate)
npe_doc(ds_decimate)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(cost_and_placement, std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> &)
npe_arg(stopping_condition, std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int)> &)
npe_arg(pre_collapse, std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int)> &)
npe_arg(post_collapse, std::function<void (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int, const bool)> &)
npe_arg(e, Eigen::MatrixXi &)
npe_arg(emap, Eigen::VectorXi &)
npe_arg(ef, Eigen::MatrixXi &)
npe_arg(ei, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::MatrixXd & u;
  Eigen::MatrixXi & g;
  Eigen::VectorXi & j;
  Eigen::VectorXi & i;
  igl::decimate(v, f, cost_and_placement, stopping_condition, pre_collapse, post_collapse, e, emap, ef, ei, u, g, j, i);
  return std::make_tuple(npe::move(u), npe::move(g), npe::move(j), npe::move(i));

npe_end_code()


