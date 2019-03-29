#include <npe.h>
#include <typedefs.h>






#include <igl/readBF.h>

const char* ds_read_bf = R"igl_Qu8mg5v7(

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

 Read a bones forest from a file, returns a list of bone roots
   Input:
     file_name  path to .bf bones tree file
   Output:
     WI  #B list of unique weight indices
     P  #B list of parent indices into B, -1 for roots
     O  #B by 3 list of tip offset vectors from parent (or position for roots)
   Returns true on success, false on errors
)igl_Qu8mg5v7";

npe_function(read_bf)
npe_doc(ds_read_bf)

npe_arg(filename, std::string &)


npe_begin_code()

  EigenDense<npe_Scalar_> wi;
  EigenDense<npe_Scalar_> p;
  EigenDense<npe_Scalar_> o;
  igl::readBF(filename, wi, p, o);
  return std::make_tuple(npe::move(wi), npe::move(p), npe::move(o));

npe_end_code()
#include <igl/readBF.h>

const char* ds_read_bf = R"igl_Qu8mg5v7(

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

 Read bone forest into pure bone-skeleton format, expects only bones (no
   point handles), and that a root in the .bf <---> no weight attachment.
  
   Input:
     file_name  path to .bf bones tree file
   Output:
     WI  #B list of unique weight indices
     P  #B list of parent indices into B, -1 for roots
     O  #B by 3 list of tip offset vectors from parent (or position for roots)
     C  #C by 3 list of absolute joint locations
     BE  #BE by 3 list of bone indices into C, in order of weight index
     P  #BE list of parent bone indices into BE, -1 means root bone
   Returns true on success, false on errors
     
   See also: readTGF, bone_parents, forward_kinematics
)igl_Qu8mg5v7";

npe_function(read_bf)
npe_doc(ds_read_bf)

npe_arg(filename, std::string &)


npe_begin_code()

  EigenDense<npe_Scalar_> wi;
  EigenDense<npe_Scalar_> bf_p;
  EigenDense<npe_Scalar_> o;
  EigenDense<npe_Scalar_> c;
  EigenDense<npe_Scalar_> be;
  EigenDense<npe_Scalar_> p;
  igl::readBF(filename, wi, bf_p, o, c, be, p);
  return std::make_tuple(npe::move(wi), npe::move(bf_p), npe::move(o), npe::move(c), npe::move(be), npe::move(p));

npe_end_code()


