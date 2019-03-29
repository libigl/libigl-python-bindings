#include <npe.h>
#include <typedefs.h>






#include <igl/faces_first.h>

const char* ds_faces_first = R"igl_Qu8mg5v7(

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

 FACES_FIRST Reorder vertices so that vertices in face list come before
   vertices that don't appear in the face list. This is especially useful if
   the face list contains only surface faces and you want surface vertices
   listed before internal vertices
  
   [RV,RT,RF,IM] = faces_first(V,T,F);
  
   Templates:
     MatV  matrix for vertex positions, e.g. MatrixXd
     MatF  matrix for face indices, e.g. MatrixXi
     VecI  vector for index map, e.g. VectorXi
   Input:
    V  # vertices by 3 vertex positions
    F  # faces by 3 list of face indices
   Output: 
    RV  # vertices by 3 vertex positions, order such that if the jth vertex is
      some face in F, and the kth vertex is not then j comes before k
    RF  # faces by 3 list of face indices, reindexed to use RV
    IM  #V by 1 list of indices such that: RF = IM(F) and RT = IM(T)
      and RV(IM,:) = V
  
  
   Example:
      Tet mesh in (V,T,F)
     faces_first(V,F,IM);
     T = T.unaryExpr(bind1st(mem_fun( static_cast<VectorXi::Scalar&
       (VectorXi::*)(VectorXi::Index)>(&VectorXi::operator())),
       &IM)).eval();
)igl_Qu8mg5v7";

npe_function(faces_first)
npe_doc(ds_faces_first)

npe_arg(v, MatV &)
npe_arg(f, MatF &)


npe_begin_code()

  MatV & rv;
  MatF & rf;
  VecI & im;
  igl::faces_first(v, f, rv, rf, im);
  return std::make_tuple(npe::move(rv), npe::move(rf), npe::move(im));

npe_end_code()
#include <igl/faces_first.h>

const char* ds_faces_first = R"igl_Qu8mg5v7(

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

 Virtual "in place" wrapper
)igl_Qu8mg5v7";

npe_function(faces_first)
npe_doc(ds_faces_first)



npe_begin_code()

  MatV & v;
  MatF & f;
  VecI & im;
  igl::faces_first(v, f, im);
  return std::make_tuple(npe::move(v), npe::move(f), npe::move(im));

npe_end_code()


