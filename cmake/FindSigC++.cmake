# Try to find the Sigc++ library
#
# Following are set afterwards:
# SIGC++_FOUND
# SIGCPP_INCLUDE_DIRS

include(FindPackageHandleStandardArgs)

set(SIGCPP_SEARCH_PATHS
        /usr
        /usr/local
        $ENV{SIGCPP_PATH})

find_path(SIGCPP_INCLUDE_DIR sigc++/sigc++.h
        PATH_SUFFIXES include/sigc++-2.0
        PATHS ${SIGCPP_SEARCH_PATHS})

find_path(SIGCPP_CONFIG_DIR sigc++config.h
        PATH_SUFFIXES lib/x86_64-linux-gnu/sigc++-2.0/include
        PATHS ${SIGCPP_SEARCH_PATHS})

set(SIGCPP_INCLUDE_DIRS ${SIGCPP_INCLUDE_DIR} ${SIGCPP_CONFIG_DIR})

find_package_handle_standard_args("SigC++" REQUIRED_VARS SIGCPP_INCLUDE_DIR SIGCPP_CONFIG_DIR)