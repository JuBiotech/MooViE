# Try to find the Freetype2 library
#
# Following are set afterwards:
# FREETYPE2_FOUND
# FREETYPE2_INCLUDE_DIR

find_path(FREETYPE2_INCLUDE NAMES freetype2/freetype/freetype.h)

message("Freetype2 include directory = ${FREETYPE2_INCLUDE}")

set(FREETYPE2_INCLUDE_DIR ${FREETYPE2_INCLUDE})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FREETYPE2 DEFAULT_MSG FREETYPE2_INCLUDE)

mark_as_advanced(FREETYPE2_INCLUDE)
