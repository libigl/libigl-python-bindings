#include <npe.h>
#include <typedefs.h>






#include <igl/collapse_edge.h>

const char* ds_collapse_edge = R"igl_Qu8mg5v7(
See collapse_edge for the documentation.
)igl_Qu8mg5v7";

npe_function(collapse_edge)
npe_doc(ds_collapse_edge)

npe_arg(e, int)
npe_arg(p, Eigen::RowVectorXd &)


npe_begin_code()

  Eigen::MatrixXd & v;
  Eigen::MatrixXi & f;
  Eigen::MatrixXi & e;
  Eigen::VectorXi & emap;
  Eigen::MatrixXi & ef;
  Eigen::MatrixXi & ei;
  int & e1;
  int & e2;
  int & f1;
  int & f2;
  igl::collapse_edge(e, p, v, f, e, emap, ef, ei, e1, e2, f1, f2);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(e), npe::move(emap), npe::move(ef), npe::move(ei), npe::move(e1), npe::move(e2), npe::move(f1), npe::move(f2));

npe_end_code()
#include <igl/collapse_edge.h>

const char* ds_collapse_edge = R"igl_Qu8mg5v7(
See collapse_edge for the documentation.
)igl_Qu8mg5v7";

npe_function(collapse_edge)
npe_doc(ds_collapse_edge)

npe_arg(e, int)
npe_arg(p, Eigen::RowVectorXd &)


npe_begin_code()

  Eigen::MatrixXd & v;
  Eigen::MatrixXi & f;
  Eigen::MatrixXi & e;
  Eigen::VectorXi & emap;
  Eigen::MatrixXi & ef;
  Eigen::MatrixXi & ei;
  igl::collapse_edge(e, p, v, f, e, emap, ef, ei);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(e), npe::move(emap), npe::move(ef), npe::move(ei));

npe_end_code()
#include <igl/collapse_edge.h>

const char* ds_collapse_edge = R"igl_Qu8mg5v7(

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

 Collapse least-cost edge from a priority queue and update queue 
  
   Inputs/Outputs:
     cost_and_placement  function computing cost of collapsing an edge and 3d
       position where it should be placed:
       cost_and_placement(V,F,E,EMAP,EF,EI,cost,placement);
       **If the edges is collapsed** then this function will be called on all
       edges of all faces previously incident on the endpoints of the
       collapsed edge.
     Q  queue containing pairs of costs and edge indices
     Qit  list of iterators so that Qit[e] --> iterator of edge e in Q
     C  #E by dim list of stored placements
)igl_Qu8mg5v7";

npe_function(collapse_edge)
npe_doc(ds_collapse_edge)

npe_arg(cost_and_placement, std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> &)


npe_begin_code()

  Eigen::MatrixXd & v;
  Eigen::MatrixXi & f;
  Eigen::MatrixXi & e;
  Eigen::VectorXi & emap;
  Eigen::MatrixXi & ef;
  Eigen::MatrixXi & ei;
  std::set<std::pair<double, int> > & q;
  std::vector<std::set<std::pair<double, int> >::iterator> & qit;
  Eigen::MatrixXd & c;
  igl::collapse_edge(cost_and_placement, v, f, e, emap, ef, ei, q, qit, c);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(e), npe::move(emap), npe::move(ef), npe::move(ei), npe::move(q), npe::move(qit), npe::move(c));

npe_end_code()
#include <igl/collapse_edge.h>

const char* ds_collapse_edge = R"igl_Qu8mg5v7(

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
       to be attempted. This function should return whether to **proceed**
       with the collapse: returning true means "yes, try to collapse",
       returning false means "No, consider this edge 'uncollapsable', behave
       as if collapse_edge(e) returned false.
     post_collapse  callback called with index of edge whose collapse was
       just attempted and a flag revealing whether this was successful.
)igl_Qu8mg5v7";

npe_function(collapse_edge)
npe_doc(ds_collapse_edge)

npe_arg(cost_and_placement, std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> &)
npe_arg(pre_collapse, std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int)> &)
npe_arg(post_collapse, std::function<void (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int, const bool)> &)


npe_begin_code()

  Eigen::MatrixXd & v;
  Eigen::MatrixXi & f;
  Eigen::MatrixXi & e;
  Eigen::VectorXi & emap;
  Eigen::MatrixXi & ef;
  Eigen::MatrixXi & ei;
  std::set<std::pair<double, int> > & q;
  std::vector<std::set<std::pair<double, int> >::iterator> & qit;
  Eigen::MatrixXd & c;
  igl::collapse_edge(cost_and_placement, pre_collapse, post_collapse, v, f, e, emap, ef, ei, q, qit, c);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(e), npe::move(emap), npe::move(ef), npe::move(ei), npe::move(q), npe::move(qit), npe::move(c));

npe_end_code()
#include <igl/collapse_edge.h>

const char* ds_collapse_edge = R"igl_Qu8mg5v7(
See collapse_edge for the documentation.
)igl_Qu8mg5v7";

npe_function(collapse_edge)
npe_doc(ds_collapse_edge)

npe_arg(cost_and_placement, std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> &)
npe_arg(pre_collapse, std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int)> &)
npe_arg(post_collapse, std::function<void (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int, const bool)> &)


npe_begin_code()

  Eigen::MatrixXd & v;
  Eigen::MatrixXi & f;
  Eigen::MatrixXi & e;
  Eigen::VectorXi & emap;
  Eigen::MatrixXi & ef;
  Eigen::MatrixXi & ei;
  std::set<std::pair<double, int> > & q;
  std::vector<std::set<std::pair<double, int> >::iterator> & qit;
  Eigen::MatrixXd & c;
  int & e;
  int & e1;
  int & e2;
  int & f1;
  int & f2;
  igl::collapse_edge(cost_and_placement, pre_collapse, post_collapse, v, f, e, emap, ef, ei, q, qit, c, e, e1, e2, f1, f2);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(e), npe::move(emap), npe::move(ef), npe::move(ei), npe::move(q), npe::move(qit), npe::move(c), npe::move(e), npe::move(e1), npe::move(e2), npe::move(f1), npe::move(f2));

npe_end_code()


