#include <npe.h>
#include <typedefs.h>






#include <igl/wire_mesh.h>

const char* ds_wire_mesh = R"igl_Qu8mg5v7(

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

 Construct a "wire" or "wireframe" or "strut" surface mesh, given a
       one-dimensional network of straight edges.
      
       Inputs:
         WV  #WV by 3 list of vertex positions
         WE  #WE by 2 list of edge indices into WV
         th  diameter thickness of wire 
         poly_size  number of sides on each wire (e.g., 4 would produce wires by
           connecting rectangular prisms).
         solid  whether to resolve self-intersections to
           create a "solid" output mesh (cf., [Zhou et al. 2016]
       Outputs:
         V  #V by 3 list of output vertices
         F  #F by 3 list of output triangle indices into V
         J  #F list of indices into [0,#WV+#WE) revealing "birth simplex" of
           output faces J(j) < #WV means the face corresponds to the J(j)th
           vertex in WV. J(j) >= #WV means the face corresponds to the
           (J(j)-#WV)th edge in WE.
)igl_Qu8mg5v7";

npe_function(wire_mesh)
npe_doc(ds_wire_mesh)

npe_arg(wv, dense_float, dense_double)
npe_arg(we, dense_float, dense_double)
npe_arg(th, double)
npe_arg(poly_size, int)
npe_arg(solid, bool)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::wire_mesh(wv, we, th, poly_size, solid, v, f, j);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(j));

npe_end_code()
#include <igl/wire_mesh.h>

const char* ds_wire_mesh = R"igl_Qu8mg5v7(

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

 Default with solid=true
)igl_Qu8mg5v7";

npe_function(wire_mesh)
npe_doc(ds_wire_mesh)

npe_arg(wv, dense_float, dense_double)
npe_arg(we, dense_float, dense_double)
npe_arg(th, double)
npe_arg(poly_size, int)


npe_begin_code()

  EigenDense<npe_Scalar_> v;
  EigenDense<npe_Scalar_> f;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::wire_mesh(wv, we, th, poly_size, v, f, j);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(j));

npe_end_code()


