cmake_minimum_required (VERSION 3.1)
project (MooViE)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
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
include_directories(${INCLUDE_DIR} "${INCLUDE_DIR}/thirdparty/tclap" ${FREETYPE2_INCLUDE_DIR} ${SIGCPP_CONFIG_DIR} ${SIGCPP_INCLUDE_DIR} ${CAIRO_INCLUDE_DIR} ${CAIROMM_CONFIG_DIR} ${CAIROMM_INCLUDE_DIR})

# Build MooViE library
add_library (libmoovie SHARED "")
target_sources(libmoovie PUBLIC "${SRC_DIR}/DataSet.cpp" "${SRC_DIR}/Scale.cpp" "${SRC_DIR}/Color.cpp" "${SRC_DIR}/Configuration.cpp" "${SRC_DIR}/OutputGrid.cpp" "${SRC_DIR}/IOVector.cpp" "${SRC_DIR}/CairoDrawer.cpp" "${SRC_DIR}/Scene.cpp" "${SRC_DIR}/Utils.cpp" "${SRC_DIR}/InputAxis.cpp")
set_target_properties(libmoovie PROPERTIES OUTPUT_NAME moovie)
install(FILES "${INCLUDE_DIR}/DataSet.h" "${INCLUDE_DIR}/Scale.h" "${INCLUDE_DIR}/Color.h" "${INCLUDE_DIR}/Configuration.h" "${INCLUDE_DIR}/OutputGrid.h" "${INCLUDE_DIR}/IOVector.h" "${INCLUDE_DIR}/CairoDrawer.h" "${INCLUDE_DIR}/Scene.h" "${INCLUDE_DIR}/Utils.h" "${INCLUDE_DIR}/InputAxis.h" "${INCLUDE_DIR}/Coordinates.h" "${INCLUDE_DIR}/DrawerProperties.h" "${INCLUDE_DIR}/Label.h" "${INCLUDE_DIR}/Mapper.h" "${INCLUDE_DIR}/TextProperties.h" "${INCLUDE_DIR}/Triangle.h" "${INCLUDE_DIR}/Drawer.h" DESTINATION /usr/include/moovie)
install (TARGETS libmoovie DESTINATION /usr/lib)

# Build MooViE executable
add_executable (moovie "${SRC_DIR}/moovie.cpp")
add_dependencies (moovie libmoovie)
target_link_libraries(moovie PUBLIC libmoovie ${CAIRO_LIBRARY_LOC} ${CAIROMM_LIBRARY_LOC})
install (TARGETS moovie DESTINATION /usr/bin)
