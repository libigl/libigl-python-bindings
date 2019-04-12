# Prepare dependencies
#
# For each third-party library, if the appropriate target doesn't exist yet,
# download it via external project, and add_subdirectory to build it alongside
# this project.

### Configuration
set(LIBIGL_ROOT     "${CMAKE_CURRENT_LIST_DIR}/..")

# Download and update 3rdparty libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
include(PyiglDownloadExternal)

################################################################################
# Required libraries
################################################################################

SET(NPE_WITH_EIGEN ${LIBIGL_EXTERNAL}/libigl/external/eigen)

SET(LIBIGL_EIGEN_VERSION "3.3.7" CACHE STRING "" FORCE)
SET(LIBIGL_EIGEN_MD5 "f2a417d083fe8ca4b8ed2bc613d20f07" CACHE STRING "" FORCE)

pyigl_download_igl()
pyigl_download_numpyeigen()
list(APPEND CMAKE_MODULE_PATH ${LIBIGL_EXTERNAL}/libigl/cmake)
include(LibiglDownloadExternal)
igl_download_tutorial_data()


