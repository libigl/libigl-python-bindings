#include <npe.h>
#include <typedefs.h>
#include <igl/seam_edges.h>

const char* ds_seam_edges = R"igl_Qu8mg5v7(

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

 Finds all UV-space boundaries of a mesh.
  
   Inputs:
     V  #V by dim list of positions of the input mesh.
     TC  #TC by 2 list of 2D texture coordinates of the input mesh
     F  #F by 3 list of triange indices into V representing a
       manifold-with-boundary triangle mesh
     FTC  #F by 3 list of indices into TC for each corner
   Outputs:
     seams  Edges where the forwards and backwards directions have different
       texture coordinates, as a #seams-by-4 matrix of indices. Each row is
       organized as [ forward_face_index, forward_face_vertex_index,
       backwards_face_index, backwards_face_vertex_index ] such that one side
       of the seam is the edge:
           F[ seams( i, 0 ), seams( i, 1 ) ], F[ seams( i, 0 ), (seams( i, 1 ) + 1) % 3 ]
       and the other side is the edge:
           F[ seams( i, 2 ), seams( i, 3 ) ], F[ seams( i, 2 ), (seams( i, 3 ) + 1) % 3 ]
     boundaries  Edges with only one incident triangle, as a #boundaries-by-2
       matrix of indices. Each row is organized as 
           [ face_index, face_vertex_index ]
       such that the edge is:
           F[ boundaries( i, 0 ), boundaries( i, 1 ) ], F[ boundaries( i, 0 ), (boundaries( i, 1 ) + 1) % 3 ]
     foldovers  Edges where the two incident triangles fold over each other
       in UV-space, as a #foldovers-by-4 matrix of indices.
       Each row is organized as [ forward_face_index, forward_face_vertex_index,
       backwards_face_index, backwards_face_vertex_index ]
       such that one side of the foldover is the edge:
         F[ foldovers( i, 0 ), foldovers( i, 1 ) ], F[ foldovers( i, 0 ), (foldovers( i, 1 ) + 1) % 3 ]
       and the other side is the edge:
         F[ foldovers( i, 2 ), foldovers( i, 3 ) ], F[ foldovers( i, 2 ), (foldovers( i, 3 ) + 1) % 3 ]
)igl_Qu8mg5v7";

npe_function(seam_edges)
npe_doc(ds_seam_edges)

npe_arg(v, dense_float, dense_double)
npe_arg(tc, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(ftc, dense_float, dense_double)


npe_begin_code()

  EigenDense<npe_Scalar_> seams;
  EigenDense<npe_Scalar_> boundaries;
  EigenDense<npe_Scalar_> foldovers;
  igl::seam_edges(v, tc, f, ftc, seams, boundaries, foldovers);
  return std::make_tuple(npe::move(seams), npe::move(boundaries), npe::move(foldovers));

npe_end_code()


