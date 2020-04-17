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
        SOURCE_DIR   ${PYLIBIGL_EXTERNAL}/${name}
        DOWNLOAD_DIR ${PYLIBIGL_EXTERNAL}/.cache/${name}
        QUIET
        ${pyigl_EXTRA_OPTIONS}
        ${ARGN}
    )
endfunction()

################################################################################

## libigl
function(pyigl_download_igl)
    pyigl_download_project(libigl
        GIT_REPOSITORY https://github.com/skoch9/libigl
        GIT_TAG        029808427a5e1221cb84ed91b280066b21b84cd9
    )
endfunction()


## numpyeigen
function(pyigl_download_numpyeigen)
    pyigl_download_project(numpyeigen
        GIT_REPOSITORY https://github.com/fwilliams/numpyeigen
        GIT_TAG        05a22ad4f06a431bffc3860b30c00cf89e81373b
    )
endfunction()


## Test data
function(pyigl_download_test_data)
	pyigl_download_project(test_data
		SOURCE_DIR "${PYLIBIGL_EXTERNAL}/../data"
		GIT_REPOSITORY https://github.com/libigl/libigl-tests-data
		GIT_TAG        e493c6eefaabf4bfce496f0abe51d476ec28df6b
	)
endfunction()

## Tutorial data
function(pyigl_download_tutorial_data)
	pyigl_download_project(tutorial_data
		SOURCE_DIR "${PYLIBIGL_EXTERNAL}/../tutorial/data"
		GIT_REPOSITORY https://github.com/libigl/libigl-tutorial-data
		GIT_TAG        38bbed76692710af038b90c69bf33d6d0f99476d
	)
endfunction()


# ## Sanitizers
# function(pyigl_download_sanitizers)
#     pyigl_download_project(sanitizers-cmake
#         GIT_REPOSITORY https://github.com/arsenm/sanitizers-cmake
#         GIT_TAG        6947cff3a9c9305eb9c16135dd81da3feb4bf87f
#     )
# endfunction()

