# Try to find the Cairo library
#
# Following are set afterwards:
# CAIRO_FOUND
# CAIRO_INCLUDE_DIRS
# CAIRO_LIBRARY

include(FindPackageHandleStandardArgs)

set(CAIRO_SEARCH_PATHS
        /usr
        /usr/local
        $ENV{CAIRO_PATH})

find_package(Freetype REQUIRED)
find_package(SigC++ REQUIRED)

find_path(CAIRO_INCLUDE_DIR cairo.h
        PATH_SUFFIXES include/cairo
        PATHS ${CAIRO_SEARCH_PATHS})

find_library(CAIRO_LIBRARY
        NAMES cairo
        PATH_SUFFIXES lib
        PATHS ${CAIRO_SEARCH_PATHS})

set(CAIRO_INCLUDE_DIRS ${CAIRO_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${SIGCPP_INCLUDE_DIRS})

find_package_handle_standard_args(Cairo REQUIRED_VARS CAIRO_LIBRARY CAIRO_INCLUDE_DIR)
