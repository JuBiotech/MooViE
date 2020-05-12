# Try to find the Sigc++ library
#
# Following are set afterwards:
# SIGC++_FOUND
# SIGCPP_INCLUDE_DIRS

include(FindPackageHandleStandardArgs)

find_package(PkgConfig)
pkg_check_modules(PC_SIGCPP QUIET "sigc++-${SigC++_FIND_VERSION}")

find_path(SIGCPP_INCLUDE_DIR
    NAMES sigc++.h
    HINTS ${PC_SIGCPP_INCLUDEDIR}
          ${PC_SIGCPP_INCLUDE_DIRS}
    PATH_SUFFIXES sigc++
)


find_path(SIGCPP_CONFIG_DIR 
    NAMES sigc++config.h
    HINTS ${PC_SIGCPP_INCLUDEDIR}
          ${PC_SIGCPP_INCLUDE_DIRS})

set(SIGCPP_INCLUDE_DIRS ${SIGCPP_INCLUDE_DIR} ${SIGCPP_CONFIG_DIR})

find_package_handle_standard_args("SigC++" REQUIRED_VARS SIGCPP_INCLUDE_DIR SIGCPP_CONFIG_DIR)
