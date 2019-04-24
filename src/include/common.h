#ifdef WIN32 // FIXME: at the end remove me at the end, usefull only fo appveyour debug
#ifdef _DEBUG
  #undef _DEBUG
  #include <python.h>
  #define _DEBUG
#else
  #include <python.h>
#endif
#endif