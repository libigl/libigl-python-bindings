cmake_minimum_required(VERSION 3.2)
project(pyigl)


if (NOT DEFINED ${LIBIGL_EXTERNAL})
  set(LIBIGL_EXTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/external)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# Color output
include(UseColors)


# Extra warnings
include(Warnings)

# Use C++11/14
include(CXXFeatures)


# Sort projects inside the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Generate position independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	foreach(config ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${config} config)
		string(REPLACE /MD /MT CMAKE_C_FLAGS_${config} "${CMAKE_C_FLAGS_${config}}")
		string(REPLACE /MD /MT CMAKE_CXX_FLAGS_${config} "${CMAKE_CXX_FLAGS_${config}}")
	endforeach()
endif()

include(PyiglDependencies)

# NumpyEigen
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${LIBIGL_EXTERNAL}/numpyeigen/cmake)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include(numpyeigen)


# LibIGL
option(LIBIGL_USE_STATIC_LIBRARY    "Use libigl as static library" OFF)
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
  include(libigl)
endif()


# A module for writing bindings with our framework
file(GLOB PYIGL_SOURCES src/*.cpp)
npe_add_module(pyigl
  BINDING_SOURCES
  ${PYIGL_SOURCES})

 #TODO move additional libs to variable
target_link_libraries(pyigl PRIVATE igl::core igl::triangle)
target_include_directories(pyigl PRIVATE "src/include")


# set(Python_ADDITIONAL_VERSIONS 3.4 3.5 3.6)
# find_package(PythonLibs REQUIRED)
# find_package(PythonInterp REQUIRED)
# target_link_libraries(pyigl PRIVATE ${PYTHON_LIBRARIES})
# set_target_properties(pyigl PROPERTIES LINK_FLAGS "-Wl,-undefined,error")
# set_target_properties(pyigl PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -msse2")
set_target_properties(pyigl PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/igl")


if(${LIBIGL_PYTHON_TESTS})
  enable_testing()
  add_subdirectory(tests)
endif()
