#include <npe.h>
#include <typedefs.h>






#include <igl/flip_edge.h>

const char* ds_flip_edge = R"igl_Qu8mg5v7(

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

 Flip an edge in a triangle mesh.  The edge specified by uei must have
   exactly **two** adjacent faces.  Violation will result in exception.
   Another warning: edge flipping could convert manifold mesh into
   non-manifold.
  
   Inputs:
     F    #F by 3 list of triangles.
     E    #F*3 by 2 list of all of directed edges
     uE   #uE by 2 list of unique undirected edges
     EMAP #F*3 list of indices into uE, mapping each directed edge to unique
          undirected edge
     uE2E #uE list of lists of indices into E of coexisting edges
     ue   index into uE the edge to be flipped.
  
   Output:
     Updated F, E, uE, EMAP and uE2E.
)igl_Qu8mg5v7";

npe_function(flip_edge)
npe_doc(ds_flip_edge)

npe_arg(uei, size_t)


npe_begin_code()

  EigenDense<npe_Scalar_> f;
  EigenDense<npe_Scalar_> e;
  EigenDense<npe_Scalar_> u_e;
  EigenDense<npe_Scalar_> emap;
  std::vector<std::vector<uE2EType> > & u_e2_e;
  igl::flip_edge(uei, f, e, u_e, emap, u_e2_e);
  return std::make_tuple(npe::move(f), npe::move(e), npe::move(u_e), npe::move(emap), npe::move(u_e2_e));

npe_end_code()


