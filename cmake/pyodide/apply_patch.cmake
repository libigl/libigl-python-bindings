# FetchContent may repeat a patch step when another dependency is reconfigured.
# Accept only the pristine or already-patched source, and fail on any mismatch.
find_package(Git REQUIRED)
execute_process(
  COMMAND "${GIT_EXECUTABLE}" apply --reverse --check "${PATCH_FILE}"
  WORKING_DIRECTORY "${SOURCE_DIR}"
  RESULT_VARIABLE already_applied
  OUTPUT_QUIET ERROR_QUIET
)
if(already_applied EQUAL 0)
  return()
endif()
execute_process(
  COMMAND "${GIT_EXECUTABLE}" apply --whitespace=nowarn "${PATCH_FILE}"
  WORKING_DIRECTORY "${SOURCE_DIR}"
  RESULT_VARIABLE result
)
if(NOT result EQUAL 0)
  message(FATAL_ERROR "Failed to apply Pyodide compatibility patch: ${PATCH_FILE}")
endif()
