# Prepare dependencies
#
# For each third-party library, if the appropriate target doesn't exist yet,
# download it via external project, and add_subdirectory to build it alongside
# this project.


# Download and update 3rdparty libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
include(PyiglDownloadExternal)

################################################################################
# Required libraries
################################################################################

SET(NPE_WITH_EIGEN ${PYLIBIGL_EXTERNAL}/libigl/external/eigen)

pyigl_download_igl()
find_package(LIBIGL REQUIRED)
pyigl_download_numpyeigen()
pyigl_download_tutorial_data()


