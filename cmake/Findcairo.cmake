# Try to find the Cairo library
#
# Following are set afterwards:
# CAIRO_FOUND
# CAIRO_INCLUDE_DIR
# CAIRO_LIBRARY_LOC
# CAIRO_LIBRARIES

find_path(CAIRO_INCLUDE NAMES cairo/cairo.h)
find_library(CAIRO_LIBRARY NAMES libcairo cairo)

message("Cairo include directory = ${CAIRO_INCLUDE}")
message("Cairo library = ${CAIRO_LIBRARY}")

set(CAIRO_INCLUDE_DIR ${CAIRO_INCLUDE})
set(CAIRO_LIBRARY_LOC ${CAIRO_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CAIRO DEFAULT_MSG CAIRO_LIBRARY CAIRO_INCLUDE)

mark_as_advanced(CAIRO_INCLUDE CAIRO_LIBRARY)
