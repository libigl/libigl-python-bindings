#include <npe.h>
#include <typedefs.h>
#include <igl/facet_components.h>

const char* ds_facet_components = R"igl_Qu8mg5v7(

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

 Compute connected components of facets based on edge-edge adjacency.
  
   Inputs:
     F  #F by 3 list of triangle indices
   Outputs:
     C  #F list of connected component ids
)igl_Qu8mg5v7";

npe_function(facet_components)
npe_doc(ds_facet_components)

npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  EigenDense<npe_Scalar_> c;
  igl::facet_components(f, c);
  return npe::move(c);

npe_end_code()






#include <igl/facet_components.h>

const char* ds_facet_components = R"igl_Qu8mg5v7(

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
     TT  #TT by 3 list of list of adjacency triangles (see
     triangle_triangle_adjacency.h)
   Outputs:
     C  #F list of connected component ids
     counts #C list of number of facets in each components
)igl_Qu8mg5v7";

npe_function(facet_components)
npe_doc(ds_facet_components)

npe_arg(tt, std::vector<std::vector<std::vector<TTIndex> > > &)


npe_begin_code()

  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> counts;
  igl::facet_components(tt, c, counts);
  return std::make_tuple(npe::move(c), npe::move(counts));

npe_end_code()


