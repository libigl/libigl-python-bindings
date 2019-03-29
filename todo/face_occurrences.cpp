#include <npe.h>
#include <typedefs.h>






#include <igl/face_occurrences.h>

const char* ds_face_occurrences = R"igl_Qu8mg5v7(

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

 Count the occruances of each face (row) in a list of face indices
   (irrespecitive of order)
   Inputs:
     F  #F by simplex-size
   Outputs
     C  #F list of counts
   Known bug: triangles/tets only (where ignoring order still gives simplex)
)igl_Qu8mg5v7";

npe_function(face_occurrences)
npe_doc(ds_face_occurrences)

npe_arg(f, std::vector<std::vector<IntegerF> > &)


npe_begin_code()

  std::vector<IntegerC> & c;
  igl::face_occurrences(f, c);
  return npe::move(c);

npe_end_code()


