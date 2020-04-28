#include <npe.h>
#include <typedefs.h>






#include <igl/background_window.h>

const char* ds_background_window = R"igl_Qu8mg5v7(

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

 Create a background window with a valid core profile opengl context
       set to current.
      
       After you're finished with this window you may call
       `glfwDestroyWindow(window)`
      
       After you're finished with glfw you should call `glfwTerminate()`
      
       Outputs:
          window  pointer to glfw window
       Returns true iff success
)igl_Qu8mg5v7";

npe_function(background_window)
npe_doc(ds_background_window)



npe_begin_code()

  int *& window;
  igl::  opengl::  glfw::background_window(window);
  return npe::move(window);

npe_end_code()


