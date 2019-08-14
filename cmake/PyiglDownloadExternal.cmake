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
        GIT_TAG        964beea9bfe373f0d398cc78ea3bd044a5c78315
    )
endfunction()


## numpyeigen
function(pyigl_download_numpyeigen)
    pyigl_download_project(numpyeigen
        GIT_REPOSITORY https://github.com/fwilliams/numpyeigen.git
        GIT_TAG        ed9b267b5a0410ea0f837ff464e1bb0122be9a91
    )
endfunction()



# ## Sanitizers
# function(pyigl_download_sanitizers)
#     pyigl_download_project(sanitizers-cmake
#         GIT_REPOSITORY https://github.com/arsenm/sanitizers-cmake.git
#         GIT_TAG        6947cff3a9c9305eb9c16135dd81da3feb4bf87f
#     )
# endfunction()

