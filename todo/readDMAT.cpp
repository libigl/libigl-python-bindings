#include <npe.h>
#include <typedefs.h>






#include <igl/readDMAT.h>

const char* ds_read_dmat = R"igl_Qu8mg5v7(
See readDMAT for the documentation.
)igl_Qu8mg5v7";

npe_function(read_dmat)
npe_doc(ds_read_dmat)

npe_arg(file_name, std::string)


npe_begin_code()

  EigenDense<npe_Scalar_> w;
  igl::readDMAT(file_name, w);
  return npe::move(w);

npe_end_code()
#include <igl/readDMAT.h>

const char* ds_read_dmat = R"igl_Qu8mg5v7(

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

 Wrapper for vector of vectors
)igl_Qu8mg5v7";

npe_function(read_dmat)
npe_doc(ds_read_dmat)

npe_arg(file_name, std::string)


npe_begin_code()

  std::vector<std::vector<double> > & w;
  igl::readDMAT(file_name, w);
  return npe::move(w);

npe_end_code()


