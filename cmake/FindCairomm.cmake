# Try to find the Cairomm-1.0 library
#
# Following are set afterwards:
# CAIROMM_FOUND
# CAIROMM_INCLUDE_DIR
# CAIROMM_LIBRARY_LOC
# CAIROMM_LIBRARIES
# CAIROMM_CONFIG_DIR

include(FindPackageHandleStandardArgs)

set(CAIROMM_SEARCH_PATHS
        /usr
        /usr/local
        $ENV{CAIROMM_PATH})

find_package(Cairo REQUIRED)

#TODO: this look-up probably only works for cairomm-1.0 and not for later versions!
find_path(CAIROMM_INCLUDE_DIR cairomm
        PATH_SUFFIXES include/cairomm-1.0
        PATHS ${CAIROMM_SEARCH_PATHS})

find_path(CAIROMM_CONFIG_DIR cairommconfig.h
        PATH_SUFFIXES lib/x86_64-linux-gnu/cairomm-1.0/include
        PATHS ${CAIROMM_SEARCH_PATHS})

find_library(CAIROMM_LIBRARY
        NAMES cairomm-1.0
        PATH_SUFFIXES lib/x86-linux-gnu
        PATHS ${CAIROMM_SEARCH_PATHS})

set(CAIROMM_INCLUDE_DIRS ${CAIROMM_INCLUDE_DIR} ${CAIROMM_CONFIG_DIR} ${CAIRO_INCLUDE_DIRS})
set(CAIROMM_LIBRARIES ${CAIROMM_LIBRARY} ${CAIRO_LIBRARY})

find_package_handle_standard_args(Cairomm REQUIRED_VARS CAIROMM_LIBRARY CAIROMM_INCLUDE_DIR CAIROMM_CONFIG_DIR)
