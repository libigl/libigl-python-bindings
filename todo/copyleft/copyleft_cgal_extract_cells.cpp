#include <npe.h>
#include <typedefs.h>
#include <igl/extract_cells.h>

const char* ds_extract_cells = R"igl_Qu8mg5v7(

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

 Extract connected 3D space partitioned by mesh (V, F).
      
       Inputs:
         V  #V by 3 array of vertices.
         F  #F by 3 array of faces.
      
       Output:
         cells  #F by 2 array of cell indices.  cells(i,0) represents the
                cell index on the positive side of face i, and cells(i,1)
                represents cell index of the negqtive side.
                By convension cell with index 0 is the infinite cell.
       Returns the number of cells
)igl_Qu8mg5v7";

npe_function(extract_cells)
npe_doc(ds_extract_cells)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)


npe_begin_code()

  EigenDense<npe_Scalar_> cells;
  igl::  copyleft::  cgal::extract_cells(v, f, cells);
  return npe::move(cells);

npe_end_code()






#include <igl/extract_cells.h>

const char* ds_extract_cells = R"igl_Qu8mg5v7(

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

 Extract connected 3D space partitioned by mesh (V, F).
      
       Inputs:
         V  #V by 3 array of vertices.
         F  #F by 3 array of faces.
         P  #F list of patch indices.
         E  #E by 2 array of vertex indices, one edge per row.
        uE    #uE by 2 list of vertex_indices, represents undirected edges.
        uE2E  #uE list of lists that maps uE to E. (a one-to-many map)
        EMAP  #F*3 list of indices into uE.
      
       Output:
         cells  #P by 2 array of cell indices.  cells(i,0) represents the
                cell index on the positive side of patch i, and cells(i,1)
                represents cell index of the negqtive side.
                By convension cell with index 0 is the infinite cell.
)igl_Qu8mg5v7";

npe_function(extract_cells)
npe_doc(ds_extract_cells)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(p, dense_float, dense_double)
npe_arg(e, dense_float, dense_double)
npe_arg(u_e, dense_float, dense_double)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)
npe_arg(emap, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> cells;
  igl::  copyleft::  cgal::extract_cells(v, f, p, e, u_e, u_e2_e, emap, cells);
  return npe::move(cells);

npe_end_code()
#include <igl/extract_cells_single_component.h>

const char* ds_extract_cells_single_component = R"igl_Qu8mg5v7(

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

 Extract connected 3D space partitioned by mesh (V,F) composed of
       **possibly multiple components** (the name of this function is
       dubious).
      
       Inputs:
         V  #V by 3 array of vertices.
         F  #F by 3 array of faces.
         P  #F list of patch indices.
         E  #E by 2 array of vertex indices, one edge per row.
        uE    #uE by 2 list of vertex_indices, represents undirected edges.
        uE2E  #uE list of lists that maps uE to E. (a one-to-many map)
        EMAP  #F*3 list of indices into uE.
       Output:
        cells  #P by 2 array of cell indices.  cells(i,0) represents the
          cell index on the positive side of patch i, and cells(i,1)
          represents cell index of the negative side.
)igl_Qu8mg5v7";

npe_function(extract_cells_single_component)
npe_doc(ds_extract_cells_single_component)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(p, dense_float, dense_double)
npe_arg(u_e, dense_float, dense_double)
npe_arg(u_e2_e, std::vector<std::vector<uE2EType> > &)
npe_arg(emap, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> cells;
  igl::  copyleft::  cgal::extract_cells_single_component(v, f, p, u_e, u_e2_e, emap, cells);
  return npe::move(cells);

npe_end_code()


