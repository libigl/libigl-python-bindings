# Refactor the cmake/setup.py build to use scikit-build
# https://github.com/wjakob/nanobind_example
# Rather than creating multiple modules and dealing with multiple __init__.py
# files, we can create a single module and use __init__.py to import the
# submodules, create one extension module with submodules
# https://stackoverflow.com/a/77020918/148668

cmake_minimum_required(VERSION 3.15...3.27)
project(pyigl)

# For std::filesystem::path (generic_string)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
# ≥17 for return value optimization 
# <20 for embree
set(CMAKE_CXX_STANDARD 17)

find_package(Python 3.8
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Enable FetchContent to download dependencies at configure time
include(FetchContent)

# Download and set up nanobind
FetchContent_Declare(
  nanobind
  GIT_REPOSITORY https://github.com/wjakob/nanobind.git
  GIT_TAG        v2.7.0
)
FetchContent_MakeAvailable(nanobind)

# Download and set up libigl
option(LIBIGL_COPYLEFT_CORE        "Build target igl_copyleft::core"       ON)
option(LIBIGL_COPYLEFT_CGAL        "Build target igl_copyleft::cgal"       ON)
option(LIBIGL_EMBREE               "Build target igl::embree"              ON)
option(LIBIGL_COPYLEFT_TETGEN      "Build target igl_copyleft::tetgen"     ON)
option(LIBIGL_RESTRICTED_TRIANGLE  "Build target igl_restricted::triangle" ON)
FetchContent_Declare(
  libigl
  GIT_REPOSITORY https://github.com/libigl/libigl.git
  GIT_TAG v2.6.0
)
FetchContent_MakeAvailable(libigl)

# set PYIGL_OUTPUT_DIRECTORY to [this dir]/igl
set(PYIGL_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/igl")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# Color output
include(UseColors)

# Extra warnings
include(Warnings)

# Use C++11/14
include(CXXFeatures)

# Generate position independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE INTERNAL "")



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
  # if(LIBIGL${prefix_uc}_${name_uc}) or name == "core"
  if(LIBIGL${prefix_uc}_${name_uc} OR name STREQUAL "core")
    if("${prefix}" STREQUAL "copyleft")
      if("${name}" STREQUAL "core")
        set(subpath "copyleft")
      else()
        set(subpath "copyleft/${name}")
      endif()
    elseif("${name}" STREQUAL "core")
      set(subpath "")
    else() # "" or "restricted"
      set(subpath "${name}")
    endif()
    file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/${subpath}/*.cpp")

    ## Just compile a single file
    #list(FILTER sources EXCLUDE REGEX ".*/module\\.cpp$")
    #list(GET sources 0 sources)
    #list(APPEND sources "${CMAKE_CURRENT_SOURCE_DIR}/src/${subpath}/module.cpp")

    message(STATUS "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$")
    message(STATUS "${prefix} ${name} sources: ${sources}")

    set(BINDING_SOURCES ${sources})
    list(FILTER BINDING_SOURCES EXCLUDE REGEX ".*/module\\.cpp$")

    # keep just the first in the list and overwrite BINDING_SOURCES

    # Generate the function calls based on filenames
    set(BINDING_DECLARATIONS "")
    foreach(source_file ${BINDING_SOURCES})
      get_filename_component(filename ${source_file} NAME_WE)
      set(BINDING_DECLARATIONS "${BINDING_DECLARATIONS}extern void bind_${filename}(nb::module_ &m);\n")
      set(BINDING_INVOCATIONS "${BINDING_INVOCATIONS}    bind_${filename}(m);\n")
    endforeach()
    # make a temporary folder in the build directory to store the generated files
    set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/include/${subpath}")
    file(MAKE_DIRECTORY "${generated_dir}")
    # write contents into BINDING_DECLARATIONS.h and BINDING_INVOCATIONS.h
    file(WRITE "${generated_dir}/BINDING_DECLARATIONS.in" "${BINDING_DECLARATIONS}")
    file(WRITE "${generated_dir}/BINDING_INVOCATIONS.in" "${BINDING_INVOCATIONS}")

    set(target_name "pyigl${prefix_lc}_${name}")
    nanobind_add_module(
      ${target_name} 
      STABLE_ABI
      ${sources})

    # important for scikit-build
    install(TARGETS ${target_name} LIBRARY DESTINATION  "igl/${subpath}")


    if("${name}" STREQUAL "core")
      target_link_libraries(${target_name} PRIVATE igl::core)
    else()
      target_link_libraries(${target_name} PRIVATE igl::core igl${prefix_lc}::${name})
    endif()
    target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
    target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
    set(output_dir "${PYIGL_OUTPUT_DIRECTORY}/${subpath}")
    file(MAKE_DIRECTORY ${output_dir})
    file(WRITE "${output_dir}/__init__.py" "from .${target_name} import *\n")
    install(FILES "${output_dir}/__init__.py" DESTINATION "igl/${subpath}")

    set_target_properties(${target_name} PROPERTIES 
        LIBRARY_OUTPUT_DIRECTORY         "${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY         "${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
    )
    set(PYI_OUTPUT "${output_dir}/${target_name}.pyi")
    nanobind_add_stub(
      ${target_name}_stub
      MODULE ${target_name}
      OUTPUT ${PYI_OUTPUT}
      PYTHON_PATH $<TARGET_FILE_DIR:${target_name}>
      DEPENDS ${target_name}
    )
    install(FILES "${PYI_OUTPUT}" DESTINATION "igl/${subpath}")

    # just to add dependency?
    if("${name}" STREQUAL "core")
    else()
      target_link_libraries(pyigl_core INTERFACE ${target_name})
    endif()
  endif()
endfunction()

pyigl_include("" "core")
if(LIBIGL_COPYLEFT_CORE)
  pyigl_include("copyleft" "core")
endif()
if(LIBIGL_COPYLEFT_CGAL)
  pyigl_include("copyleft" "cgal")
endif()
if(LIBIGL_EMBREE)
  pyigl_include("" "embree")
endif()
if(LIBIGL_COPYLEFT_TETGEN)
  pyigl_include("copyleft" "tetgen")
endif()
if(LIBIGL_RESTRICTED_TRIANGLE)
  pyigl_include("restricted" "triangle")
endif()



