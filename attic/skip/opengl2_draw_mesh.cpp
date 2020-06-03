#include <npe.h>
#include <typedefs.h>






#include <igl/draw_mesh.h>

const char* ds_draw_mesh = R"igl_Qu8mg5v7(

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

 Draw ../opengl/OpenGL_ commands needed to display a mesh with normals
    
     Inputs:
       V  #V by 3 eigen Matrix of mesh vertex 3D positions
       F  #F by 3|4 eigen Matrix of face (triangle/quad) indices
       N  #V|#F by 3 eigen Matrix of 3D normals
)igl_Qu8mg5v7";

npe_function(draw_mesh)
npe_doc(ds_draw_mesh)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(n, Eigen::MatrixXd &)


npe_begin_code()

  igl::  opengl2::draw_mesh(v, f, n);
  return ;

npe_end_code()
#include <igl/draw_mesh.h>

const char* ds_draw_mesh = R"igl_Qu8mg5v7(

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

 Draw ../opengl/OpenGL_ commands needed to display a mesh with normals and per-vertex
     colors
    
     Inputs:
       V  #V by 3 eigen Matrix of mesh vertex 3D positions
       F  #F by 3|4 eigen Matrix of face (triangle/quad) indices
       N  #V|#F by 3 eigen Matrix of 3D normals
       C  #V|#F|1 by 3 eigen Matrix of RGB colors
)igl_Qu8mg5v7";

npe_function(draw_mesh)
npe_doc(ds_draw_mesh)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(n, Eigen::MatrixXd &)
npe_arg(c, Eigen::MatrixXd &)


npe_begin_code()

  igl::  opengl2::draw_mesh(v, f, n, c);
  return ;

npe_end_code()
#include <igl/draw_mesh.h>

const char* ds_draw_mesh = R"igl_Qu8mg5v7(

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
       V  #V by 3 eigen Matrix of mesh vertex 3D positions
       F  #F by 3|4 eigen Matrix of face (triangle/quad) indices
       N  #V|#F by 3 eigen Matrix of 3D normals
       C  #V|#F|1 by 3 eigen Matrix of RGB colors
       TC  #V|#F|1 by 3 eigen Matrix of Texture Coordinates
)igl_Qu8mg5v7";

npe_function(draw_mesh)
npe_doc(ds_draw_mesh)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(n, Eigen::MatrixXd &)
npe_arg(c, Eigen::MatrixXd &)
npe_arg(tc, Eigen::MatrixXd &)


npe_begin_code()

  igl::  opengl2::draw_mesh(v, f, n, c, tc);
  return ;

npe_end_code()
#include <igl/draw_mesh.h>

const char* ds_draw_mesh = R"igl_Qu8mg5v7(

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

 Draw ../opengl/OpenGL_ commands needed to display a mesh with normals, per-vertex
     colors and LBS weights
    
     Inputs:
       V  #V by 3 eigen Matrix of mesh vertex 3D positions
       F  #F by 3|4 eigen Matrix of face (triangle/quad) indices
       N  #V by 3 eigen Matrix of mesh vertex 3D normals
       C  #V by 3 eigen Matrix of mesh vertex RGB colors
       TC  #V by 3 eigen Matrix of mesh vertex UC coorindates between 0 and 1
       W  #V by #H eigen Matrix of per mesh vertex, per handle weights
       W_index  Specifies the index of the "weight" vertex attribute: see
         glBindAttribLocation, if W_index is 0 then weights are ignored
       WI  #V by #H eigen Matrix of per mesh vertex, per handle weight ids
       WI_index  Specifies the index of the "weight" vertex attribute: see
         glBindAttribLocation, if WI_index is 0 then weight indices are ignored
)igl_Qu8mg5v7";

npe_function(draw_mesh)
npe_doc(ds_draw_mesh)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(n, Eigen::MatrixXd &)
npe_arg(c, Eigen::MatrixXd &)
npe_arg(tc, Eigen::MatrixXd &)
npe_arg(w, Eigen::MatrixXd &)
npe_arg(w_index, GLuint)
npe_arg(wi, Eigen::MatrixXi &)
npe_arg(wi_index, GLuint)


npe_begin_code()

  igl::  opengl2::draw_mesh(v, f, n, c, tc, w, w_index, wi, wi_index);
  return ;

npe_end_code()
#include <igl/draw_mesh.h>

const char* ds_draw_mesh = R"igl_Qu8mg5v7(

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

 Draw ../opengl/OpenGL_ commands needed to display a mesh with normals, per-vertex
     colors and LBS weights
    
     Inputs:
       V  #V by 3 eigen Matrix of mesh vertex 3D positions
       F  #F by 3|4 eigen Matrix of face (triangle/quad) indices
       N  #V by 3 eigen Matrix of mesh vertex 3D normals
       NF  #F by 3 eigen Matrix of face (triangle/quad) normal indices, <0
         means no normal
       C  #V by 3 eigen Matrix of mesh vertex RGB colors
       TC  #V by 3 eigen Matrix of mesh vertex UC coorindates between 0 and 1
       TF  #F by 3 eigen Matrix of face (triangle/quad) texture indices, <0
         means no texture
       W  #V by #H eigen Matrix of per mesh vertex, per handle weights
       W_index  Specifies the index of the "weight" vertex attribute: see
         glBindAttribLocation, if W_index is 0 then weights are ignored
       WI  #V by #H eigen Matrix of per mesh vertex, per handle weight ids
       WI_index  Specifies the index of the "weight" vertex attribute: see
         glBindAttribLocation, if WI_index is 0 then weight indices are ignored
)igl_Qu8mg5v7";

npe_function(draw_mesh)
npe_doc(ds_draw_mesh)

npe_arg(v, Eigen::MatrixXd &)
npe_arg(f, Eigen::MatrixXi &)
npe_arg(n, Eigen::MatrixXd &)
npe_arg(nf, Eigen::MatrixXi &)
npe_arg(c, Eigen::MatrixXd &)
npe_arg(tc, Eigen::MatrixXd &)
npe_arg(tf, Eigen::MatrixXi &)
npe_arg(w, Eigen::MatrixXd &)
npe_arg(w_index, GLuint)
npe_arg(wi, Eigen::MatrixXi &)
npe_arg(wi_index, GLuint)


npe_begin_code()

  igl::  opengl2::draw_mesh(v, f, n, nf, c, tc, tf, w, w_index, wi, wi_index);
  return ;

npe_end_code()


