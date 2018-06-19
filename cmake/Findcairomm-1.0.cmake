# Try to find the Cairomm-1.0 library
#
# Following are set afterwards:
# CAIROMM_FOUND
# CAIROMM_INCLUDE_DIR
# CAIROMM_LIBRARY_LOC
# CAIROMM_LIBRARIES
# CAIROMM_CONFIG_DIR

find_path(CAIROMM_INCLUDE NAMES cairomm-1.0/cairomm)
find_path(CAIROMM_CONFIG NAMES cairomm-1.0/include HINTS /usr/lib/x86_64-linux-gnu)
find_library(CAIROMM_LIBRARY NAMES libcairomm-1.0 cairomm-1.0)

set(CAIROMM_INCLUDE_DIR "${CAIROMM_INCLUDE}/cairomm-1.0")
set(CAIROMM_CONFIG_DIR "${CAIROMM_CONFIG}/cairomm-1.0/include")
set(CAIROMM_LIBRARY_LOC ${CAIROMM_LIBRARY})

message("Cairomm include directory = ${CAIROMM_INCLUDE_DIR}")
message("Cairomm config directory = ${CAIROMM_CONFIG_DIR}")
message("Cairomm library = ${CAIROMM_LIBRARY_LOC}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CAIROMM DEFAULT_MSG CAIROMM_LIBRARY CAIROMM_CONFIG CAIROMM_INCLUDE)

mark_as_advanced(CAIROMM_INCLUDE CAIROMM_CONFIG CAIROMM_LIBRARY)
