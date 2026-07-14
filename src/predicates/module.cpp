#include <nanobind/nanobind.h>
#include <igl/predicates/exactinit.h>
namespace nb = nanobind;
#include "predicates/BINDING_DECLARATIONS.in"
NB_MODULE(pyigl_predicates, m) {
  m.doc() = "libigl predicates module python bindings";
  igl::predicates::exactinit();
  #include "predicates/BINDING_INVOCATIONS.in"
}
