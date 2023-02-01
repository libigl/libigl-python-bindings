# Prepare dependencies
#
# For each third-party library, if the appropriate target doesn't exist yet,
# download it via external project, and add_subdirectory to build it alongside
# this project.


# Download and update 3rdparty libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)

################################################################################
# Required libraries
################################################################################

SET(NPE_WITH_EIGEN ${PYLIBIGL_EXTERNAL}/libigl/external/eigen  CACHE INTERNAL "")

include(FetchContent)

FetchContent_Declare(
    libigl
    GIT_REPOSITORY https://github.com/libigl/libigl.git
    GIT_TAG 238a607032d725cbf1b99cad2077516b1ee066d8
)
FetchContent_MakeAvailable(libigl)

FetchContent_Declare(
  numpyeigen
  GIT_REPOSITORY https://github.com/fwilliams/numpyeigen.git
  GIT_TAG        05a22ad4f06a431bffc3860b30c00cf89e81373b)
# NumpyEigen's CMakeLists sets NPE_PYTHON_EXECUTABLE without a way to override,
# so we must include directly rather that using FetchContent_MakeAvailable
#FetchContent_MakeAvailable(numpyeigen)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PYLIBIGL_EXTERNAL}/numpyeigen/cmake)
include(numpyeigen)

if(${PY_IGL_PYTHON_TESTS})
  FetchContent_Declare(test_data
    SOURCE_DIR "${PYLIBIGL_EXTERNAL}/../data"
    GIT_REPOSITORY https://github.com/libigl/libigl-tests-data.git
    GIT_TAG        19cedf96d70702d8b3a83eb27934780c542356fe)
  FetchContent_MakeAvailable(test_data)
endif()

if(${PY_IGL_PYTHON_TUTORIAL})
  FetchContent_Declare(tutorial_data
    SOURCE_DIR "${PYLIBIGL_EXTERNAL}/../tutorial/data"
    GIT_REPOSITORY https://github.com/libigl/libigl-tutorial-data.git
    GIT_TAG        c1f9ede366d02e3531ecbaec5e3769312f31cccd)
  FetchContent_MakeAvailable(tutorial_data)
endif()

