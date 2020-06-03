#include <npe.h>
#include <typedefs.h>






#include <igl/relabel_small_immersed_cells.h>

const char* ds_relabel_small_immersed_cells = R"igl_Qu8mg5v7(

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
         num_patches  number of patches
         P  #F list of patch ids.
         num_cells    number of cells
         C  #P by 2 list of cell ids on each side of each patch.
         vol_threshold  Volume threshold, cells smaller than this
                        and is completely immersed will be relabeled.
      
       In/Output:
         W  #F by 2 cell labels.  W(i,0) is the label on the positive side of
            face i, W(i,1) is the label on the negative side of face i.  W
            will be modified in place by this method.
)igl_Qu8mg5v7";

npe_function(relabel_small_immersed_cells)
npe_doc(ds_relabel_small_immersed_cells)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(num_patches, size_t)
npe_arg(p, dense_float, dense_double)
npe_arg(num_cells, size_t)
npe_arg(c, dense_float, dense_double)
npe_arg(vol_threashold, FT)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::  copyleft::  cgal::relabel_small_immersed_cells(v, f, num_patches, p, num_cells, c, vol_threashold, w);
  return npe::move(w);

npe_end_code()


