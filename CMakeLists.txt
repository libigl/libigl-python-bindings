cmake_minimum_required(VERSION 3.16.0)
project(pyigl)

if (NOT DEFINED ${PYLIBIGL_EXTERNAL})
  set(PYLIBIGL_EXTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/external)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# Color output
include(UseColors)

# Extra warnings
include(Warnings)

# Use C++11/14
include(CXXFeatures)

# Generate position independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE INTERNAL "")

include(PyiglDependencies)

if(NOT TARGET igl::core)
  include(libigl)
endif()

# A module for writing bindings with our framework
file(GLOB PYIGL_SOURCES src/*.cpp)

npe_add_module(pyigl
  BINDING_SOURCES
  ${PYIGL_SOURCES}
  ${PYIGL_SOURCES_COPYLEFT})

#TODO move additional libs to variable
target_link_libraries(pyigl PRIVATE igl::core)
target_include_directories(pyigl PRIVATE "src/include")

add_library(pyigl_classes MODULE classes/classes.cpp)
target_link_libraries(pyigl_classes PRIVATE npe igl::core)
target_link_libraries(pyigl_classes PRIVATE pybind11::module)
set_target_properties(pyigl_classes PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")
target_include_directories(pyigl_classes PRIVATE "src/include")
target_include_directories(pyigl_classes PRIVATE "${PYLIBIGL_EXTERNAL}/numpyeigen/src")

# Sort projects inside the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config)
    string(REPLACE /MD /MT CMAKE_C_FLAGS_${config} "${CMAKE_C_FLAGS_${config}}")
    string(REPLACE /MD /MT CMAKE_CXX_FLAGS_${config} "${CMAKE_CXX_FLAGS_${config}}")
  endforeach()
endif()
