################################################################################
include(DownloadProject)

# With CMake 3.8 and above, we can hide warnings about git being in a
# detached head by passing an extra GIT_CONFIG option
if(NOT (${CMAKE_VERSION} VERSION_LESS "3.8.0"))
    set(pyigl_EXTRA_OPTIONS "GIT_CONFIG advice.detachedHead=false")
else()
    set(pyigl_EXTRA_OPTIONS "")
endif()

# Shortcut function
function(pyigl_download_project name)
    download_project(
        PROJ         ${name}
        SOURCE_DIR   ${LIBIGL_EXTERNAL}/${name}
        DOWNLOAD_DIR ${LIBIGL_EXTERNAL}/.cache/${name}
        QUIET
        ${pyigl_EXTRA_OPTIONS}
        ${ARGN}
    )
endfunction()

################################################################################

## libigl
function(pyigl_download_igl)
    pyigl_download_project(libigl
        GIT_REPOSITORY https://github.com/skoch9/libigl.git
        GIT_TAG        dc1a4bbd4714adf7975fa9eb636c045f7d3fbccc
    )
endfunction()


## numpyeigen
function(pyigl_download_numpyeigen)
    pyigl_download_project(numpyeigen
        GIT_REPOSITORY https://github.com/fwilliams/numpyeigen.git
        GIT_TAG        3ba543b00b3da2a974f9cdc59e4e648f0dc48135
    )
endfunction()



# ## Sanitizers
# function(pyigl_download_sanitizers)
#     pyigl_download_project(sanitizers-cmake
#         GIT_REPOSITORY https://github.com/arsenm/sanitizers-cmake.git
#         GIT_TAG        6947cff3a9c9305eb9c16135dd81da3feb4bf87f
#     )
# endfunction()

