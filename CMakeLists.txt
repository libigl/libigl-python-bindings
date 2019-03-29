cmake_minimum_required(VERSION 3.2)
project(pyigl)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")

if (NOT DEFINED ${LIBIGL_EXTERNAL})
  set(LIBIGL_EXTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/../external)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)
include(LibiglDownloadExternal)
igl_download_numpyeigen()
igl_download_tutorial_data()

# NumpyEigen
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${LIBIGL_EXTERNAL}/numpyeigen/cmake)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include(numpyeigen)


# LibIGL
option(LIBIGL_USE_STATIC_LIBRARY "Use libigl as static library" OFF)
option(LIBIGL_WITH_ANTTWEAKBAR      "Use AntTweakBar"    OFF)
option(LIBIGL_WITH_CGAL             "Use CGAL"           OFF)
option(LIBIGL_WITH_COMISO           "Use CoMiso"         OFF)
option(LIBIGL_WITH_CORK             "Use Cork"           OFF)
option(LIBIGL_WITH_EMBREE           "Use Embree"         OFF)
option(LIBIGL_WITH_LIM              "Use LIM"            OFF)
option(LIBIGL_WITH_MATLAB           "Use Matlab"         OFF)
option(LIBIGL_WITH_MOSEK            "Use MOSEK"          OFF)
option(LIBIGL_WITH_NANOGUI          "Use Nanogui menu"   OFF)
option(LIBIGL_WITH_OPENGL           "Use OpenGL"         OFF)
option(LIBIGL_WITH_OPENGL_GLFW      "Use GLFW"           OFF)
option(LIBIGL_WITH_PNG              "Use PNG"            OFF)
option(LIBIGL_WITH_PYTHON           "Use Python"         OFF)
option(LIBIGL_WITH_TETGEN           "Use Tetgen"         OFF)
option(LIBIGL_WITH_TRIANGLE         "Use Triangle"       ON)
option(LIBIGL_WITH_VIEWER           "Use OpenGL viewer"  OFF)
option(LIBIGL_WITH_XML              "Use XML"            OFF)
option(LIBIGL_PYTHON_TESTS          "Run Python tests"   ON)

if(NOT TARGET igl::core)
  list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../shared/cmake")
  include(libigl)
endif()


# A module for writing bindings with our framework
file(GLOB PYIGL_SOURCES src/*.cpp)
npe_add_module(pyigl
  BINDING_SOURCES
  ${PYIGL_SOURCES})

target_link_libraries(pyigl PRIVATE igl::core igl::triangle) #TODO move additional libs to variable
target_include_directories(pyigl PRIVATE ${PYBIND_11_DIR}/include src/include)


#set(Python_ADDITIONAL_VERSIONS 3.4 3.5 3.6)
#find_package(PythonLibs REQUIRED)
#find_package(PythonInterp REQUIRED)
#target_link_libraries(pyigl PRIVATE ${PYTHON_LIBRARIES})
#set_target_properties(pyigl PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
set_target_properties(pyigl PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -msse2")
set_target_properties(pyigl PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../igl")


if(${LIBIGL_PYTHON_TESTS})
  enable_testing()
  add_subdirectory(tests)
endif()
