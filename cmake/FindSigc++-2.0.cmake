# Try to find the Sigc++ library
#
# Following are set afterwards:
# SIGC++_FOUND
# SIGCPP_INCLUDE_DIR
# SIGCPP_CONFIG_DIR

find_path(SIGCPP_INCLUDE NAMES sigc++-2.0/sigc++/sigc++.h)
find_path(SIGCPP_CONFIG NAMES sigc++-2.0/include HINTS /usr/lib/x86_64-linux-gnu)

message("Sigc++ include directory = ${SIGCPP_INCLUDE}")
message("Sigc++ config directory = ${SIGCPP_CONFIG}")

set(SIGCPP_INCLUDE_DIR ${SIGCPP_INCLUDE})
set(SIGCPP_CONFIG_DIR ${SIGCPP_CONFIG})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SIGC++ DEFAULT_MSG SIGCPP_CONFIG SIGCPP_INCLUDE)

mark_as_advanced(SIGCPP_INCLUDE SIGCPP_CONFIG)
