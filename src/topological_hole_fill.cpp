#include <npe.h>
#include <typedefs.h>






#include <igl/topological_hole_fill.h>

const char* ds_topological_hole_fill = R"igl_Qu8mg5v7(

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

 Topological fill hole on a mesh, with one additional vertex each hole
   Index of new abstract vertices will be F.maxCoeff() + (index of hole)
  
   Inputs:
     F  #F by simplex-size list of element indices
     b  #b boundary indices to preserve
     holes vector of hole loops to fill
   Outputs:
     F_filled  input F stacked with filled triangles.
  
)igl_Qu8mg5v7";

npe_function(topological_hole_fill)
npe_doc(ds_topological_hole_fill)

npe_arg(f, dense_i32, dense_i64)
npe_arg(b, dense_f32, dense_f64)
npe_arg(holes, std::vector<VectorIndex> &)


npe_begin_code()

  EigenDense<npe_Scalar_> f_filled;
  igl::topological_hole_fill(f, b, holes, f_filled);
  return npe::move(f_filled);

npe_end_code()


