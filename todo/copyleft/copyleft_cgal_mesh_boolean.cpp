#include <npe.h>
#include <typedefs.h>






#include <igl/mesh_boolean.h>

const char* ds_mesh_boolean = R"igl_Qu8mg5v7(

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

  MESH_BOOLEAN Compute boolean csg operations on "solid", consistently
        oriented meshes.
      
        Inputs:
          VA  #VA by 3 list of vertex positions of first mesh
          FA  #FA by 3 list of triangle indices into VA
          VB  #VB by 3 list of vertex positions of second mesh
          FB  #FB by 3 list of triangle indices into VB
          type  type of boolean operation
        Outputs:
          VC  #VC by 3 list of vertex positions of boolean result mesh
          FC  #FC by 3 list of triangle indices into VC
          J  #FC list of indices into [FA;FA.rows()+FB] revealing "birth" facet
        Returns true if inputs induce a piecewise constant winding number
        field and type is valid
      
        See also: mesh_boolean_cork, intersect_other,
        remesh_self_intersections
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)
npe_arg(type, igl::MeshBooleanType &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::mesh_boolean(va, fa, vb, fb, type, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()
#include <igl/mesh_boolean.h>

const char* ds_mesh_boolean = R"igl_Qu8mg5v7(
See mesh_boolean for the documentation.
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)
npe_arg(type_str, std::string &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::mesh_boolean(va, fa, vb, fb, type_str, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()
#include <igl/mesh_boolean.h>

const char* ds_mesh_boolean = R"igl_Qu8mg5v7(

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
          VA  #VA by 3 list of vertex positions of first mesh
          FA  #FA by 3 list of triangle indices into VA
          VB  #VB by 3 list of vertex positions of second mesh
          FB  #FB by 3 list of triangle indices into VB
          wind_num_op  function handle for filtering winding numbers from
            tuples of integer values to [0,1] outside/inside values
          keep  function handle for determining if a patch should be "kept"
            in the output based on the winding number on either side
        Outputs:
          VC  #VC by 3 list of vertex positions of boolean result mesh
          FC  #FC by 3 list of triangle indices into VC
          J  #FC list of indices into [FA;FB] revealing "birth" facet
        Returns true iff inputs induce a piecewise constant winding number
          field
      
        See also: mesh_boolean_cork, intersect_other,
        remesh_self_intersections
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)
npe_arg(wind_num_op, std::function<int (const Eigen::Matrix<int, 1, Eigen::Dynamic>)> &)
npe_arg(keep, std::function<int (const int, const int)> &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::mesh_boolean(va, fa, vb, fb, wind_num_op, keep, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()
#include <igl/mesh_boolean.h>

const char* ds_mesh_boolean = R"igl_Qu8mg5v7(

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

  MESH_BOOLEAN Variadic boolean operations
      
        Inputs:
          Vlist  k-long list of lists of mesh vertex positions
          Flist  k-long list of lists of mesh face indices, so that Flist[i] indexes
            vertices in Vlist[i]
          wind_num_op  function handle for filtering winding numbers from
            n-tuples of integer values to [0,1] outside/inside values
          keep  function handle for determining if a patch should be "kept"
            in the output based on the winding number on either side
        Outputs:
          VC  #VC by 3 list of vertex positions of boolean result mesh
          FC  #FC by 3 list of triangle indices into VC
          J  #FC list of indices into [Flist[0];Flist[1];...;Flist[k]]
            revealing "birth" facet
        Returns true iff inputs induce a piecewise constant winding number
          field
      
        See also: mesh_boolean_cork, intersect_other,
        remesh_self_intersections
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(vlist, std::vector<DerivedV> &)
npe_arg(flist, std::vector<DerivedF> &)
npe_arg(wind_num_op, std::function<int (const Eigen::Matrix<int, 1, Eigen::Dynamic>)> &)
npe_arg(keep, std::function<int (const int, const int)> &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::mesh_boolean(vlist, flist, wind_num_op, keep, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()
#include <igl/mesh_boolean.h>

const char* ds_mesh_boolean = R"igl_Qu8mg5v7(
See mesh_boolean for the documentation.
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(vlist, std::vector<DerivedV> &)
npe_arg(flist, std::vector<DerivedF> &)
npe_arg(type, igl::MeshBooleanType &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::mesh_boolean(vlist, flist, type, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()
#include <igl/mesh_boolean.h>

const char* ds_mesh_boolean = R"igl_Qu8mg5v7(

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

 Given a merged mesh (V,F) and list of sizes of inputs
      
       Inputs:
         V  #V by 3 list of merged mesh vertex positions
         F  #F by 3 list of merged mesh face indices so that first sizes(0)
           faces come from the first input, and the next sizes(1) faces come
           from the second input, and so on.
         sizes  #inputs list of sizes so that sizes(i) is the #faces in the
           ith input
          wind_num_op  function handle for filtering winding numbers from
            tuples of integer values to [0,1] outside/inside values
          keep  function handle for determining if a patch should be "kept"
            in the output based on the winding number on either side
        Outputs:
          VC  #VC by 3 list of vertex positions of boolean result mesh
          FC  #FC by 3 list of triangle indices into VC
          J  #FC list of birth parent indices
       
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(vv, dense_float, dense_double)
npe_arg(ff, dense_float, dense_double)
npe_arg(sizes, dense_float, dense_double)
npe_arg(wind_num_op, std::function<int (const Eigen::Matrix<int, 1, Eigen::Dynamic>)> &)
npe_arg(keep, std::function<int (const int, const int)> &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  EigenDense<npe_Scalar_> j;
  igl::  copyleft::  cgal::mesh_boolean(vv, ff, sizes, wind_num_op, keep, vc, fc, j);
  return std::make_tuple(npe::move(vc), npe::move(fc), npe::move(j));

npe_end_code()
#include <igl/mesh_boolean.h>

const char* ds_mesh_boolean = R"igl_Qu8mg5v7(

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
          VA  #VA by 3 list of vertex positions of first mesh
          FA  #FA by 3 list of triangle indices into VA
          VB  #VB by 3 list of vertex positions of second mesh
          FB  #FB by 3 list of triangle indices into VB
          type  type of boolean operation
        Outputs:
          VC  #VC by 3 list of vertex positions of boolean result mesh
          FC  #FC by 3 list of triangle indices into VC
        Returns true ff inputs induce a piecewise constant winding number
          field and type is valid
)igl_Qu8mg5v7";

npe_function(mesh_boolean)
npe_doc(ds_mesh_boolean)

npe_arg(va, dense_float, dense_double)
npe_arg(fa, dense_float, dense_double)
npe_arg(vb, dense_float, dense_double)
npe_arg(fb, dense_float, dense_double)
npe_arg(type, igl::MeshBooleanType &)


npe_begin_code()

  EigenDense<npe_Scalar_> vc;
  EigenDense<npe_Scalar_> fc;
  igl::  copyleft::  cgal::mesh_boolean(va, fa, vb, fb, type, vc, fc);
  return std::make_tuple(npe::move(vc), npe::move(fc));

npe_end_code()


