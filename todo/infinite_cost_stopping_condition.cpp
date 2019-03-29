#include <npe.h>
#include <typedefs.h>






#include <igl/infinite_cost_stopping_condition.h>

const char* ds_infinite_cost_stopping_condition = R"igl_Qu8mg5v7(

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

 Stopping condition function compatible with igl::decimate. The output
   function handle will return true if cost of next edge is infinite.
  
   Inputs:
     cost_and_placement  handle being used by igl::collapse_edge
   Outputs:
     stopping_condition
  
)igl_Qu8mg5v7";

npe_function(infinite_cost_stopping_condition)
npe_doc(ds_infinite_cost_stopping_condition)

npe_arg(cost_and_placement, std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> &)


npe_begin_code()

  std::function<bool (const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const std::set<std::pair<double, int> > &, const std::vector<std::set<std::pair<double, int> >::iterator> &, const Eigen::MatrixXd &, const int, const int, const int, const int, const int)> & stopping_condition;
  igl::infinite_cost_stopping_condition(cost_and_placement, stopping_condition);
  return npe::move(stopping_condition);

npe_end_code()
#include <igl/infinite_cost_stopping_condition.h>

const char* ds_infinite_cost_stopping_condition = R"igl_Qu8mg5v7(
See infinite_cost_stopping_condition for the documentation.
)igl_Qu8mg5v7";

npe_function(infinite_cost_stopping_condition)
npe_doc(ds_infinite_cost_stopping_condition)

npe_arg(, Eigen::MatrixXd &)
npe_arg(, Eigen::MatrixXi &)
npe_arg(, Eigen::MatrixXi &)
npe_arg(, Eigen::VectorXi &)
npe_arg(, Eigen::MatrixXi &)
npe_arg(, Eigen::MatrixXi &)
npe_arg(, std::set<std::pair<double, int> > &)
npe_arg(, std::vector<std::set<std::pair<double, int> >::iterator> &)
npe_arg(, Eigen::MatrixXd &)
npe_arg(, int)
npe_arg(, int)
npe_arg(, int)
npe_arg(, int)
npe_arg(, int)
npe_arg(cost_and_placement, std::function<void (const int, const Eigen::MatrixXd &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, const Eigen::VectorXi &, const Eigen::MatrixXi &, const Eigen::MatrixXi &, double &, Eigen::RowVectorXd &)> &)


npe_begin_code()

  igl::infinite_cost_stopping_condition(, , , , , , , , , , , , , , cost_and_placement);
  return ;

npe_end_code()


