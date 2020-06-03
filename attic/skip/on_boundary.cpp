#include <npe.h>
#include <typedefs.h>
#include <igl/on_boundary.h>

const char* ds_on_boundary = R"igl_Qu8mg5v7(

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
     DerivedI  bool-value: i.e. from MatrixXi
     DerivedC  bool-value: i.e. from MatrixXi
)igl_Qu8mg5v7";

npe_function(on_boundary)
npe_doc(ds_on_boundary)

npe_arg(t, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> i;
  EigenDense<npe_Scalar_> c;
  igl::on_boundary(t, i, c);
  return std::make_tuple(npe::move(i), npe::move(c));

npe_end_code()






#include <igl/on_boundary.h>

const char* ds_on_boundary = R"igl_Qu8mg5v7(

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

 ON_BOUNDARY Determine boundary facets of mesh elements stored in T
  
   Templates:
     IntegerT  integer-value: i.e. int
     IntegerF  integer-value: i.e. int
   Input:
    T  triangle|tetrahedron index list, m by 3|4, where m is the number of
      elements
   Output:
    I  m long list of bools whether tet is on boundary
    C  m by 3|4 list of bools whether opposite facet is on boundary
  
)igl_Qu8mg5v7";

npe_function(on_boundary)
npe_doc(ds_on_boundary)

npe_arg(t, std::vector<std::vector<IntegerT> > &)


npe_begin_code()

  std::vector<bool> & i;
  std::vector<std::vector<bool> > & c;
  igl::on_boundary(t, i, c);
  return std::make_tuple(npe::move(i), npe::move(c));

npe_end_code()


