#include <npe.h>
#include <typedefs.h>






#include <igl/voxel_grid.h>

const char* ds_voxel_grid = R"igl_Qu8mg5v7(

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

 Construct the cell center positions of a regular voxel grid (lattice) made
   of perfectly square voxels.
   
   Inputs:
     box  bounding box to enclose by grid
     s  number of cell centers on largest side (including 2*pad_count)
     pad_count  number of cells beyond box
   Outputs:
     GV  side(0)*side(1)*side(2) by 3 list of cell center positions
     side  3-long list of dimension of voxel grid
)igl_Qu8mg5v7";

npe_function(voxel_grid)
npe_doc(ds_voxel_grid)

npe_arg(box, Eigen::AlignedBox<Scalar, 3> &)
npe_arg(s, int)
npe_arg(pad_count, int)


npe_begin_code()

  EigenDense<npe_Scalar_> gv;
  EigenDense<npe_Scalar_> side;
  igl::voxel_grid(box, s, pad_count, gv, side);
  return std::make_tuple(npe::move(gv), npe::move(side));

npe_end_code()


