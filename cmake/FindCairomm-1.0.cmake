# Try to find the Cairomm-1.0 library
#
# Following are set afterwards:
# CAIROMM_FOUND
# CAIROMM_INCLUDE_DIR
# CAIROMM_LIBRARY_DIR
# CAIROMM_LIBRARIES
# CAIROMM_CONFIG_DIR

find_path(CAIROMM_INCLUDE NAMES cairomm-1.0/cairomm.h)
find_path(CAIROMM_CONFIG NAMES cairomm-1.0/include)
find_library(CAIROMM_LIBRARY NAMES libcairomm-1.0 cairomm-1.0)

message("Cairomm include directory = ${CAIROMM_INCLUDE}")
message("Cairomm config directory = ${CAIROMM_CONFIG}")
message("Cairomm library = ${CAIROMM_LIBRARY}")

set(CAIROMM_INCLUDE_DIR ${CAIROMM_INCLUDE})
set(CAIROMM_CONFIG_DIR ${CAIROMM_CONFIG})
set(CAIROMM_LIBRARY_DIR ${CAIROMM_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CAIROMM DEFAULT_MSG CAIROMM_LIBRARY CAIRO_CONFIG CAIROMM_INCLUDE)

mark_as_advanced(CAIROMM_INCLUDE CAIROMM_CONFIG CAIROMM_LIBRARY)
