#include <npe.h>
#include <typedefs.h>






#include <igl/qslim_optimal_collapse_edge_callbacks.h>

const char* ds_qslim_optimal_collapse_edge_callbacks = R"igl_Qu8mg5v7(

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

 Prepare callbacks for decimating edges using the qslim optimal placement
   metric.
  
   Inputs:
     E  #E by 2 list of working edges
     quadrics  reference to list of working per vertex quadrics 
     v1  working variable to maintain end point of collapsed edge
     v2  working variable to maintain end point of collapsed edge
   Outputs
     cost_and_placement  callback for evaluating cost of edge collapse and
       determining placement of vertex (see collapse_edge)
     pre_collapse  callback before edge collapse (see collapse_edge)
     post_collapse  callback after edge collapse (see collapse_edge)
)igl_Qu8mg5v7";

npe_function(qslim_optimal_collapse_edge_callbacks)
npe_doc(ds_qslim_optimal_collapse_edge_callbacks)



npe_begin_code()

  Eigen::MatrixXi & e;
  std::vector<std::tuple<Eigen::MatrixXd, Eigen::RowVectorXd, double> > & quadrics;
  int & v1;
  int & v2;
  std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> & cost_and_placement;
  std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int)> & pre_collapse;
  std::function<void (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int, const bool)> & post_collapse;
  igl::qslim_optimal_collapse_edge_callbacks(e, quadrics, v1, v2, cost_and_placement, pre_collapse, post_collapse);
  return std::make_tuple(npe::move(e), npe::move(quadrics), npe::move(v1), npe::move(v2), npe::move(cost_and_placement), npe::move(pre_collapse), npe::move(post_collapse));

npe_end_code()


