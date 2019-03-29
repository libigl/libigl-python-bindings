#include <npe.h>
#include <typedefs.h>






#include <igl/ray_mesh_intersect.h>

const char* ds_ray_mesh_intersect = R"igl_Qu8mg5v7(

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

 Shoot a ray against a mesh (V,F) and collect all hits.
  
   Inputs:
     source  3-vector origin of ray
     dir  3-vector direction of ray
     V  #V by 3 list of mesh vertex positions
     F  #F by 3 list of mesh face indices into V
   Outputs:
      hits  **sorted** list of hits
   Returns true if there were any hits (hits.size() > 0)
  
)igl_Qu8mg5v7";

npe_function(ray_mesh_intersect)
npe_doc(ds_ray_mesh_intersect)

npe_arg(source, dense_f32, dense_f64)
npe_arg(dir, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  std::vector<igl::Hit> & hits;
  igl::ray_mesh_intersect(source, dir, v, f, hits);
  return npe::move(hits);

npe_end_code()
#include <igl/ray_mesh_intersect.h>

const char* ds_ray_mesh_intersect = R"igl_Qu8mg5v7(

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

 Outputs:
     hit  first hit, set only if it exists
   Returns true if there was a hit
)igl_Qu8mg5v7";

npe_function(ray_mesh_intersect)
npe_doc(ds_ray_mesh_intersect)

npe_arg(source, dense_f32, dense_f64)
npe_arg(dir, dense_f32, dense_f64)
npe_arg(v, dense_f32, dense_f64)
npe_arg(f, dense_i32, dense_i64)


npe_begin_code()

  igl::Hit & hit;
  igl::ray_mesh_intersect(source, dir, v, f, hit);
  return npe::move(hit);

npe_end_code()


