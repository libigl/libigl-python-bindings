#include <npe.h>
#include <typedefs.h>
#include <igl/is_boundary_edge.h>

const char* ds_is_boundary_edge = R"igl_Qu8mg5v7(

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

  IS_BOUNDARY_EDGE Determine for each edge E if it is a "boundary edge" in F.
    Boundary edges are undirected edges which occur only once.
   
    Inputs:
      E  #E by 2 list of edges
      F  #F by 3 list of triangles
    Outputs:
      B  #E list bools. true iff unoriented edge occurs exactly once in F
        (non-manifold and non-existant edges will be false)
   
)igl_Qu8mg5v7";

npe_function(is_boundary_edge)
npe_doc(ds_is_boundary_edge)

npe_arg(e, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> b;
  igl::is_boundary_edge(e, f, b);
  return npe::move(b);

npe_end_code()
#include <igl/is_boundary_edge.h>

const char* ds_is_boundary_edge = R"igl_Qu8mg5v7(

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

 Wrapper where Edges should also be computed from F
     E  #E by 2 list of edges
     EMAP  #F*3 list of indices mapping allE to E
)igl_Qu8mg5v7";

npe_function(is_boundary_edge)
npe_doc(ds_is_boundary_edge)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> b;
  EigenDense<npe_Scalar_> e;
  EigenDense<npe_Scalar_> emap;
  igl::is_boundary_edge(f, b, e, emap);
  return std::make_tuple(npe::move(b), npe::move(e), npe::move(emap));

npe_end_code()


