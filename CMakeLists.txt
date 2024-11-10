cmake_minimum_required(VERSION 3.16.0)
project(pyigl)

# use C++20 (we need at least C++17 for return value optimization)
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

find_package(Python 3.8 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Enable FetchContent to download dependencies at configure time
include(FetchContent)

# Download and set up nanobind
FetchContent_Declare(
  nanobind
  GIT_REPOSITORY https://github.com/wjakob/nanobind.git
  GIT_TAG        v2.2.0
)
FetchContent_MakeAvailable(nanobind)

# Download and set up libigl
FetchContent_Declare(
  libigl
  GIT_REPOSITORY https://github.com/libigl/libigl.git
  GIT_TAG 1410ad43dff78bfaf8d8103de422fa64adfa35d5
)
FetchContent_MakeAvailable(libigl)

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

option(LIBIGL_COPYLEFT_CGAL "Build target igl_copyleft::cgal"       OFF)
option(LIBIGL_COPYLEFT_TETGEN "Build target igl_copyleft::tetgen"       OFF)
option(LIBIGL_RESTRICTED_TRIANGLE "Build target igl_restricted::triangle"       OFF)

# A module for writing bindings with our framework
file(GLOB PYIGL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(BINDING_SOURCES ${PYIGL_SOURCES})
list(REMOVE_ITEM BINDING_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/module.cpp")  # Exclude module.cpp

# Generate the function calls based on filenames
set(BINDING_DECLARATIONS "")
foreach(source_file ${BINDING_SOURCES})
    get_filename_component(filename ${source_file} NAME_WE)
    set(BINDING_DECLARATIONS "${BINDING_DECLARATIONS}extern void bind_${filename}(nb::module_ &m);\n")
    set(BINDING_INVOCATIONS "${BINDING_INVOCATIONS}    bind_${filename}(m);\n")
endforeach()
# make a temporary folder in the build directory to store the generated files
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include")
# write contents into BINDING_DECLARATIONS.h and BINDING_INVOCATIONS.h
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/include/BINDING_DECLARATIONS.in" "${BINDING_DECLARATIONS}")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/include/BINDING_INVOCATIONS.in" "${BINDING_INVOCATIONS}")

nanobind_add_module(pyigl ${PYIGL_SOURCES})

target_link_libraries(pyigl PRIVATE igl::core)
target_include_directories(pyigl PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
target_include_directories(pyigl PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(pyigl PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY "${PYIGL_OUTPUT_DIRECTORY}"
  RUNTIME_OUTPUT_DIRECTORY "${PYIGL_OUTPUT_DIRECTORY}"
  LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PYIGL_OUTPUT_DIRECTORY}"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PYIGL_OUTPUT_DIRECTORY}"
  )
