cmake_minimum_required(VERSION 3.16.0)
project(pyigl)

if (NOT DEFINED PYLIBIGL_EXTERNAL)
  set(PYLIBIGL_EXTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/external)
endif()

message(STATUS "PYIGL_OUTPUT_DIRECTORY: ${PYIGL_OUTPUT_DIRECTORY}")
if (NOT DEFINED PYIGL_OUTPUT_DIRECTORY)
  message(FATAL_ERROR "PYIGL_OUTPUT_DIRECTORY must be defined externally")
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

option(LIBIGL_COPYLEFT_CGAL "Build target igl_copyleft::cgal"       ON)
option(LIBIGL_COPYLEFT_TETGEN "Build target igl_copyleft::tetgen"       ON)
option(LIBIGL_RESTRICTED_TRIANGLE "Build target igl_restricted::triangle"       ON)
# libigl options must come before include(PyiglDependencies)
include(PyiglDependencies)
if(NOT TARGET igl::core)
  include(libigl)
endif()

# A module for writing bindings with our framework
file(GLOB PYIGL_SOURCES src/*.cpp)
npe_add_module(pyigl
  BINDING_SOURCES
  ${PYIGL_SOURCES})
target_link_libraries(pyigl PRIVATE igl::core)
target_include_directories(pyigl PRIVATE "src/include")
set_target_properties(pyigl PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY "${PYIGL_OUTPUT_DIRECTORY}"
  RUNTIME_OUTPUT_DIRECTORY "${PYIGL_OUTPUT_DIRECTORY}"
  LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PYIGL_OUTPUT_DIRECTORY}"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PYIGL_OUTPUT_DIRECTORY}"
  )

# don't need to worry about nested modules (opengl/** are the only ones and
# those probably aren't ever getting python bindings)
#
# prefix is either "", "copyleft", or "restricted"
function(pyigl_include prefix name)
  string(TOUPPER "${prefix}" prefix_uc)
  string(TOUPPER "${name}" name_uc)
  if(prefix_uc)
      string(PREPEND prefix_uc _)
  endif()
  string(TOLOWER "${prefix_uc}" prefix_lc)
  if(LIBIGL${prefix_uc}_${name_uc})
    if(${prefix} STREQUAL "copyleft")
      set(subpath "copyleft/${name}")
    else() # "" or "restricted"
      set(subpath "${name}")
    endif()
    file(GLOB sources src/${subpath}/*.cpp)
    set(target_name "pyigl${prefix_lc}_${name}")
    npe_add_module(                            ${target_name} BINDING_SOURCES ${sources})
    target_link_libraries(                     ${target_name} PRIVATE igl::core igl${prefix_lc}::${name})
    target_include_directories(                ${target_name} PRIVATE "src/include")
    set(output_dir "${PYIGL_OUTPUT_DIRECTORY}/${subpath}")
    file(MAKE_DIRECTORY ${output_dir})
    file(WRITE "${output_dir}/__init__.py" "from .${target_name} import *")
    # https://stackoverflow.com/a/56514534/148668
    set_target_properties(${target_name} PROPERTIES 
      LIBRARY_OUTPUT_DIRECTORY "${output_dir}"
      RUNTIME_OUTPUT_DIRECTORY "${output_dir}"
      LIBRARY_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${output_dir}")
    # why do this?
    target_link_libraries(     pyigl INTERFACE ${target_name})
  endif()
  # https://stackoverflow.com/a/69736197/148668 
  # https://cmake.org/cmake/help/latest/manual/cmake.1.html#cmdoption-cmake-E-arg-copy
  # until then just needlessly also copy TARGET_FILE in case TARGET_RUNTIME_DLLS is empty
  if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_custom_command(TARGET ${target_name} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target_name}> $<TARGET_RUNTIME_DLLS:${target_name}> $<TARGET_FILE_DIR:${target_name}>
      COMMAND_EXPAND_LISTS)
  endif()
endfunction()

pyigl_include("copyleft" "cgal")
pyigl_include("copyleft" "tetgen")
pyigl_include("restricted" "triangle")


file(GLOB PYIGL_CLASSES_SOURCES classes/*.cpp)
add_library(pyigl_classes MODULE ${PYIGL_CLASSES_SOURCES})
# std::variant
target_compile_features(pyigl_classes  PRIVATE cxx_std_17)
target_link_libraries(pyigl_classes PRIVATE npe igl::core)
target_link_libraries(pyigl_classes PRIVATE pybind11::module)
set_target_properties(pyigl_classes PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")
target_include_directories(pyigl_classes PRIVATE "src/include")
target_include_directories(pyigl_classes PRIVATE "${PYLIBIGL_EXTERNAL}/numpyeigen/src")
set_target_properties(pyigl_classes PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY "${PYIGL_OUTPUT_DIRECTORY}"
  RUNTIME_OUTPUT_DIRECTORY "${PYIGL_OUTPUT_DIRECTORY}"
  LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PYIGL_OUTPUT_DIRECTORY}"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PYIGL_OUTPUT_DIRECTORY}"
  )

# Sort projects inside the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config)
    string(REPLACE /MD /MT CMAKE_C_FLAGS_${config} "${CMAKE_C_FLAGS_${config}}")
    string(REPLACE /MD /MT CMAKE_CXX_FLAGS_${config} "${CMAKE_CXX_FLAGS_${config}}")
  endforeach()
endif()
