#include <npe.h>
#include <typedefs.h>
#include <igl/propagate_winding_numbers.h>

const char* ds_propagate_winding_numbers = R"igl_Qu8mg5v7(

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

 TODO: This shouldn't need to be in igl::copyleft::cgal, it should
       instead take as input an index of the ambient cell and the winding
       number vector there.
      
       Compute winding number on each side of the face.  The input mesh
       could contain multiple connected components.  The input mesh must
       represent the boundary of a valid 3D volume, which means it is
       closed, consistently oriented and induces integer winding numbers.
      
       Inputs:
         V  #V by 3 list of vertex positions.
         F  #F by 3 list of triangle indices into V.
         labels  #F list of facet labels ranging from 0 to k-1.
       Output:
         W  #F by k*2 list of winding numbers.  ``W(i,j*2)`` is the winding
            number on the positive side of facet ``i`` with respect to the
            facets labeled ``j``.  Similarly, ``W(i,j*2+1)`` is the winding
            number on the negative side of facet ``i`` with respect to the
            facets labeled ``j``.
       Returns true iff the input induces a piecewise-constant winding number
         field.
)igl_Qu8mg5v7";

npe_function(propagate_winding_numbers)
npe_doc(ds_propagate_winding_numbers)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(labels, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::  copyleft::  cgal::propagate_winding_numbers(v, f, labels, w);
  return npe::move(w);

npe_end_code()






#include <igl/propagate_winding_numbers.h>

const char* ds_propagate_winding_numbers = R"igl_Qu8mg5v7(

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
         V  #V by 3 list of vertex positions.
         F  #F by 3 list of triangle indices into V.
         uE    #uE by 2 list of vertex_indices, represents undirected edges.
         uE2E  #uE list of lists that maps uE to E. (a one-to-many map)
         num_patches  number of patches
         P  #F list of patch ids.
         num_cells    number of cells
         C  #P by 2 list of cell ids on each side of each patch.
         labels  #F list of facet labels ranging from 0 to k-1.
       Output:
         W  #F by k*2 list of winding numbers.  ``W(i,j*2)`` is the winding
            number on the positive side of facet ``i`` with respect to the
            facets labeled ``j``.  Similarly, ``W(i,j*2+1)`` is the winding
            number on the negative side of facet ``i`` with respect to the
            facets labeled ``j``.
)igl_Qu8mg5v7";

npe_function(propagate_winding_numbers)
npe_doc(ds_propagate_winding_numbers)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(u_e, dense_float, dense_double)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)
npe_arg(num_patches, size_t)
npe_arg(p, dense_float, dense_double)
npe_arg(num_cells, size_t)
npe_arg(c, dense_float, dense_double)
npe_arg(labels, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::  copyleft::  cgal::propagate_winding_numbers(v, f, u_e, u_e2_e, num_patches, p, num_cells, c, labels, w);
  return npe::move(w);

npe_end_code()


