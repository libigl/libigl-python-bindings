#include <npe.h>
#include <typedefs.h>






#include <igl/remesh_intersections.h>

const char* ds_remesh_intersections = R"igl_Qu8mg5v7(

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

 Remesh faces according to results of intersection detection and
       construction (e.g. from `igl::copyleft::cgal::intersect_other` or
       `igl::copyleft::cgal::SelfIntersectMesh`)
      
       Inputs:
         V  #V by 3 list of vertex positions
         F  #F by 3 list of triangle indices into V
         T  #F list of cgal triangles
         offending #offending map taking face indices into F to pairs of order
           of first finding and list of intersection objects from all
           intersections
         stitch_all  if true, merge all vertices with the same coordinate.
       Outputs:
         VV  #VV by 3 list of vertex positions, if stitch_all = false then
           first #V vertices will always be V
         FF  #FF by 3 list of triangle indices into V
         IF  #intersecting face pairs by 2  list of intersecting face pairs,
           indexing F
         J  #FF list of indices into F denoting birth triangle
         IM  / stitch_all = true   #VV list from 0 to #VV-1
             \ stitch_all = false  #VV list of indices into VV of unique vertices.
      
)igl_Qu8mg5v7";

npe_function(remesh_intersections)
npe_doc(ds_remesh_intersections)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(t, std::vector<CGAL::Triangle_3<Kernel> > &)
npe_arg(offending, std::map<typename DerivedF::Index, std::vector<std::pair<typename DerivedF::Index, CGAL::Object> > > &)


npe_begin_code()

  bool stitch_all;
  EigenDense<npe_Scalar_> vv;
  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> im;
  igl::  copyleft::  cgal::remesh_intersections(v, f, t, offending, stitch_all, vv, ff, j, im);
  return std::make_tuple(npe::move(stitch_all), npe::move(vv), npe::move(ff), npe::move(j), npe::move(im));

npe_end_code()
#include <igl/remesh_intersections.h>

const char* ds_remesh_intersections = R"igl_Qu8mg5v7(

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

 Same as above except stitch_all is assumed "false"
)igl_Qu8mg5v7";

npe_function(remesh_intersections)
npe_doc(ds_remesh_intersections)

npe_arg(v, dense_float, dense_double)
npe_arg(f, dense_int, dense_long)
npe_arg(t, std::vector<CGAL::Triangle_3<Kernel> > &)
npe_arg(offending, std::map<typename DerivedF::Index, std::vector<std::pair<typename DerivedF::Index, CGAL::Object> > > &)


npe_begin_code()

  EigenDense<npe_Scalar_> vv;
  EigenDense<npe_Scalar_> ff;
  EigenDense<npe_Scalar_> j;
  EigenDense<npe_Scalar_> im;
  igl::  copyleft::  cgal::remesh_intersections(v, f, t, offending, vv, ff, j, im);
  return std::make_tuple(npe::move(vv), npe::move(ff), npe::move(j), npe::move(im));

npe_end_code()


