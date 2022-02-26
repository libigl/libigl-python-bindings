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

option(PY_IGL_PYTHON_TESTS          "Run Python tests"   ON)
message(STATUS "PY_IGL_PYTHON_TESTS: ${PY_IGL_PYTHON_TESTS}")


option(LIBIGL_COPYLEFT_CGAL "Build target igl_copyleft::cgal"       ON)
# libigl options must come before include(PyiglDependencies)
include(PyiglDependencies)
if(NOT TARGET igl::core)
  include(libigl)
endif()

# NumpyEigen
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PYLIBIGL_EXTERNAL}/numpyeigen/cmake)
# Generate position independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include(numpyeigen)

# A module for writing bindings with our framework
file(GLOB PYIGL_SOURCES src/*.cpp)
npe_add_module(pyigl
  BINDING_SOURCES
  ${PYIGL_SOURCES})
target_link_libraries(pyigl PRIVATE igl::core)
target_include_directories(pyigl PRIVATE "src/include")

if(LIBIGL_COPYLEFT_CGAL)
  file(GLOB PYIGL_COPYLEFT_CGAL_SOURCES src/copyleft/cgal/*.cpp)
  npe_add_module(pyigl_copyleft_cgal
    BINDING_SOURCES
    ${PYIGL_COPYLEFT_CGAL_SOURCES})
  target_link_libraries(pyigl_copyleft_cgal PRIVATE igl::core igl_copyleft::cgal)
  target_include_directories(pyigl_copyleft_cgal PRIVATE "src/include")
  target_link_libraries(pyigl INTERFACE pyigl_copyleft_cgal)
endif()


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
    # LIST(APPEND CMAKE_CXX_FLAGS_${config} "/Zm")
	endforeach()
endif()

# set(Python_ADDITIONAL_VERSIONS 3.4 3.5 3.6)
# find_package(PythonLibs REQUIRED)
# find_package(PythonInterp REQUIRED)
# target_link_libraries(pyigl PRIVATE ${PYTHON_LIBRARIES})
# set_target_properties(pyigl PROPERTIES LINK_FLAGS "-Wl,-undefined,error")
#set_target_properties(pyigl PROPERTIES LINK_FLAGS "-Wl,--no-undefined")
# set_target_properties(pyigl PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -msse2")
# set_target_properties(pyigl PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/igl")

if(${PY_IGL_PYTHON_TESTS})
  pyigl_download_test_data()
  enable_testing()
  add_subdirectory(tests)
endif()
