#include <npe.h>
#include <typedefs.h>






#include <igl/submesh_aabb_tree.h>

const char* ds_submesh_aabb_tree = R"igl_Qu8mg5v7(

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

 Build an AABB tree for a submesh indicated by a face selection list I
       of a full mesh (V,F)
      
       Inputs:
         V  #V by 3 array of vertices.
         F  #F by 3 array of faces.
         I  #I list of triangle indices to consider.
       Outputs:
         tree  aabb containing triangles of (V,F(I,:))
         triangles  #I list of cgal triangles
         in_I  #F list of whether in submesh
)igl_Qu8mg5v7";

npe_function(submesh_aabb_tree)
npe_doc(ds_submesh_aabb_tree)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(i, dense_float, dense_double)


npe_begin_code()

  CGAL::AABB_tree<CGAL::AABB_traits<Kernel, CGAL::AABB_triangle_primitive<Kernel, typename std::vector<typename Kernel::Triangle_3>::iterator> > > & tree;
  std::vector<typename Kernel::Triangle_3> & triangles;
  std::vector<bool> & in_i;
  igl::  copyleft::  cgal::submesh_aabb_tree(v, f, i, tree, triangles, in_i);
  return std::make_tuple(npe::move(tree), npe::move(triangles), npe::move(in_i));

npe_end_code()


