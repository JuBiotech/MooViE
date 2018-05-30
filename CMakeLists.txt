cmake_minimum_required (VERSION 2.6)
project (MooViE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_MODULE_PATH}/cmake")
set(CMAKE_CXX_STANDARD 11)

# Find important libraries
# Moovie uses Cairomm-1.0, which depends on
# - Cairo, which depends on
#   - freetype2
#   - sigc++-2.0
find_package (freetype2 REQUIRED)
find_package (sigc++-2.0 REQUIRED)
find_package (cairo REQUIRED)
find_package (cairomm-1.0 REQUIRED)

# Add includes and linking
include_directories("include" "include/thirdparty/tclap" FREETYPE2_INCLUDE_DIR SIGCPP_CONFIG_DIR SIGCPP_INCLUDE_DIR CAIRO_INCLUDE_DIR CAIROMM_CONFIG_DIR CAIRO_CAIROMM_INCLUDE_DIR)
link_directories(CAIRO_LIBRARY_DIR CAIROMM_LIBRARY_DIR)

# Build MooViE library
file (GLOB SOURCES src/*.cpp)
list(REMOVE_ITEM SOURCES "moovie.cpp")
add_library (libmoovie SHARED ${SOURCES})
install (TARGETS libmoovie DESTINATION /usr/lib RENAME moovie)

# Build MooViE executable
add_executable (moovie "src/moovie.cpp")
add_dependencies (moovie libmoovie)
target_link_libraries(moovie libmoovie)
install (TARGETS moovie DESTINATION /usr/bin)
