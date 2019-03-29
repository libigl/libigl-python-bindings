#include <npe.h>
#include <typedefs.h>






#include <igl/simplify_polyhedron.h>

const char* ds_simplify_polyhedron = R"igl_Qu8mg5v7(

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

 Simplify a polyhedron represented as a triangle mesh (OV,OF) by collapsing
   any edge that doesn't contribute to defining surface's pointset. This
   _would_ also make sense for open and non-manifold meshes, but the current
   implementation only works with closed manifold surfaces with well defined
   triangle normals.
  
   Inputs:
     OV  #OV by 3 list of input mesh vertex positions
     OF  #OF by 3 list of input mesh triangle indices into OV
   Outputs:
     V  #V by 3 list of output mesh vertex positions
     F  #F by 3 list of input mesh triangle indices into V
     J  #F list of indices into OF of birth parents
)igl_Qu8mg5v7";

npe_function(simplify_polyhedron)
npe_doc(ds_simplify_polyhedron)

npe_arg(ov, Eigen::MatrixXd &)
npe_arg(of, Eigen::MatrixXi &)


npe_begin_code()

  Eigen::MatrixXd & v;
  Eigen::MatrixXi & f;
  Eigen::VectorXi & j;
  igl::simplify_polyhedron(ov, of, v, f, j);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(j));

npe_end_code()


