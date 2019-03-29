#include <npe.h>
#include <typedefs.h>






#include <igl/limit_faces.h>

const char* ds_limit_faces = R"igl_Qu8mg5v7(

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

 LIMIT_FACES limit given faces F to those which contain (only) indices found
   in L.
  
   [LF] = limit_faces(F,L,exclusive);
   [LF,in] = limit_faces(F,L,exclusive);
  
   Templates:
     MatF matrix type of faces, matrixXi
     VecL  matrix type of vertex indices, VectorXi
   Inputs:
     F  #F by 3 list of face indices
     L  #L by 1 list of allowed indices
     exclusive  flag specifying whether a face is included only if all its
       indices are in L, default is false
   Outputs:
     LF  #LF by 3 list of remaining faces after limiting
     in  #F list of whether given face was included
  
)igl_Qu8mg5v7";

npe_function(limit_faces)
npe_doc(ds_limit_faces)

npe_arg(f, MatF &)
npe_arg(l, VecL &)
npe_arg(exclusive, bool)


npe_begin_code()

  MatF & lf;
  igl::limit_faces(f, l, exclusive, lf);
  return npe::move(lf);

npe_end_code()


