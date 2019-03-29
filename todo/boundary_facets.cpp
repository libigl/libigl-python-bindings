#include <npe.h>
#include <typedefs.h>
#include <igl/boundary_facets.h>

const char* ds_boundary_facets = R"igl_Qu8mg5v7(

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

 Templates:
     DerivedT  integer-value: i.e. from MatrixXi
     DerivedF  integer-value: i.e. from MatrixXi
)igl_Qu8mg5v7";

npe_function(boundary_facets)
npe_doc(ds_boundary_facets)

npe_arg(t, dense_f32, dense_f64)


npe_begin_code()

  EigenDense<npe_Scalar_> f;
  igl::boundary_facets(t, f);
  return npe::move(f);

npe_end_code()
#include <igl/boundary_facets.h>

const char* ds_boundary_facets = R"igl_Qu8mg5v7(

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

 Same as above but returns F
)igl_Qu8mg5v7";

npe_function(boundary_facets)
npe_doc(ds_boundary_facets)

npe_arg(t, dense_f32, dense_f64)


npe_begin_code()

  igl::boundary_facets(t);
  return ;

npe_end_code()






#include <igl/boundary_facets.h>

const char* ds_boundary_facets = R"igl_Qu8mg5v7(

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

 BOUNDARY_FACETS Determine boundary faces (edges) of tetrahedra (triangles)
   stored in T (analogous to qptoolbox's `outline` and `boundary_faces`).
  
   Templates:
     IntegerT  integer-value: e.g. int
     IntegerF  integer-value: e.g. int
   Input:
    T  tetrahedron (triangle) index list, m by 4 (3), where m is the number of tetrahedra
   Output:
    F  list of boundary faces, n by 3 (2), where n is the number of boundary faces
  
  
)igl_Qu8mg5v7";

npe_function(boundary_facets)
npe_doc(ds_boundary_facets)

npe_arg(t, std::vector<std::vector<IntegerT> > &)


npe_begin_code()

  std::vector<std::vector<IntegerF> > & f;
  igl::boundary_facets(t, f);
  return npe::move(f);

npe_end_code()


