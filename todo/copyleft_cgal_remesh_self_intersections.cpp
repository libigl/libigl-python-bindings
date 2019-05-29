#include <npe.h>
#include <typedefs.h>






#include <igl/remesh_self_intersections.h>

const char* ds_remesh_self_intersections = R"igl_Qu8mg5v7(

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

 Given a triangle mesh (V,F) compute a new mesh (VV,FF) which is the same
       as (V,F) except that any self-intersecting triangles in (V,F) have been
       subdivided (new vertices and face created) so that the self-intersection
       contour lies exactly on edges in (VV,FF). New vertices will appear in
       original faces or on original edges. New vertices on edges are "merged"
       only across original faces sharing that edge. This means that if the input
       triangle mesh is a closed manifold the output will be too.
      
       Inputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices into V
         params  struct of optional parameters
       Outputs:
         VV  #VV by 3 list of vertex positions
         FF  #FF by 3 list of triangle indices into VV
         IF  #intersecting face pairs by 2  list of intersecting face pairs,
           indexing F
         J  #FF list of indices into F denoting birth triangle
         IM  #VV list of indices into VV of unique vertices.
      
       Known bugs: If an existing edge in (V,F) lies exactly on another face then
       any resulting additional vertices along that edge may not get properly
       connected so that the output mesh has the same global topology. This is
       because 
      
       Example:
            resolve intersections
           igl::copyleft::cgal::remesh_self_intersections(V,F,params,VV,FF,IF,J,IM);
            _apply_ duplicate vertex mapping IM to FF
           for_each(FF.data(),FF.data()+FF.size(),[&IM](int & a){a=IM(a);});
            remove any vertices now unreferenced after duplicate mapping.
           igl::remove_unreferenced(VV,FF,SV,SF,UIM);
            Now (SV,SF) is ready to extract outer hull
           igl::copyleft::cgal::outer_hull(SV,SF,G,J,flip);
      
)igl_Qu8mg5v7";

npe_function(remesh_self_intersections)
npe_doc(ds_remesh_self_intersections)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(params, igl::copyleft::cgal::RemeshSelfIntersectionsParam &)


npe_begin_code()

  EigenDense<npe_Scalar_> vv;
  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> if;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> im;
  igl::  copyleft::  cgal::remesh_self_intersections(v, f, params, vv, ff, if, j, im);
  return std::make_tuple(npe::move(vv), npe::move(ff), npe::move(if), npe::move(j), npe::move(im));

npe_end_code()


