# General settings
cmake_minimum_required (VERSION 3.1)
project (MooViE)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set (CMAKE_CXX_STANDARD 11)

# Set code location variables
set (MOOVIE_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set (MOOVIE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (DESKTOP_SRC_DIR ${PROJECT_SOURCE_DIR}/src/desktop)
set (DESKTOP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/desktop)
set (DESKTOP_UI_DIR ${PROJECT_SOURCE_DIR}/ui)

# Find important libraries
# Moovie uses Cairomm-1.0, which depends on
# - Cairo, which depends on
#   - freetype2
#   - sigc++-2.0
find_package (freetype2 REQUIRED)
find_package (sigc++-2.0 REQUIRED)
find_package (cairo REQUIRED)
find_package (cairomm-1.0 REQUIRED)
find_package (Qt4 REQUIRED QtGui QtWebKit)

# Structure files
set (MOOVIE_SRC
	${MOOVIE_SRC_DIR}/DataSet.cpp
	${MOOVIE_SRC_DIR}/Scale.cpp
	${MOOVIE_SRC_DIR}/Color.cpp
	${MOOVIE_SRC_DIR}/Configuration.cpp
	${MOOVIE_SRC_DIR}/OutputGrid.cpp
	${MOOVIE_SRC_DIR}/IOVector.cpp
	${MOOVIE_SRC_DIR}/CairoDrawer.cpp
	${MOOVIE_SRC_DIR}/Scene.cpp
	${MOOVIE_SRC_DIR}/Utils.cpp
	${MOOVIE_SRC_DIR}/InputAxis.cpp
)

set (MOOVIE_INCLUDES
	${MOOVIE_INCLUDE_DIR}/DataSet.h
	${MOOVIE_INCLUDE_DIR}/Scale.h
	${MOOVIE_INCLUDE_DIR}/Color.h
	${MOOVIE_INCLUDE_DIR}/Configuration.h
	${MOOVIE_INCLUDE_DIR}/OutputGrid.h
	${MOOVIE_INCLUDE_DIR}/IOVector.h
	${MOOVIE_INCLUDE_DIR}/CairoDrawer.h
	${MOOVIE_INCLUDE_DIR}/Scene.h
	${MOOVIE_INCLUDE_DIR}/Utils.h
	${MOOVIE_INCLUDE_DIR}/InputAxis.h
	${MOOVIE_INCLUDE_DIR}/Coordinates.h
	${MOOVIE_INCLUDE_DIR}/DrawerProperties.h
	${MOOVIE_INCLUDE_DIR}/Label.h
	${MOOVIE_INCLUDE_DIR}/Mapper.h
	${MOOVIE_INCLUDE_DIR}/TextProperties.h
	${MOOVIE_INCLUDE_DIR}/Triangle.h
	${MOOVIE_INCLUDE_DIR}/Drawer.h
)

set (DESKTOP_SRC
)

set (DESKTOP_INCLUDES
)

set (UIS
)


# Add includes and linking
include_directories (${MOOVIE_INCLUDE_DIR} ${MOOVIE_INCLUDE_DIR}/thirdparty/tclap ${FREETYPE2_INCLUDE_DIR} ${SIGCPP_CONFIG_DIR} ${SIGCPP_INCLUDE_DIR} ${CAIRO_INCLUDE_DIR} ${CAIROMM_CONFIG_DIR} ${CAIROMM_INCLUDE_DIR})


# Build MooViE library
add_library (libmoovie STATIC "")
target_sources (libmoovie PUBLIC ${MOOVIE_SRC})
set_target_properties (libmoovie PROPERTIES OUTPUT_NAME moovie)
install (FILES ${MOOVIE_INCLUDES} DESTINATION /usr/include/moovie)
install (TARGETS libmoovie DESTINATION /usr/lib)


# Build MooViE executable
add_executable (moovie ${MOOVIE_SRC_DIR}/moovie.cpp)
add_dependencies (moovie libmoovie)
target_link_libraries (moovie PUBLIC libmoovie ${CAIRO_LIBRARY_LOC} ${CAIROMM_LIBRARY_LOC})
install (TARGETS moovie DESTINATION /usr/bin)


# Build Qt4 application
find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})
include_directories (${CMAKE_BINARY_DIR} ${DESKTOP_INCLUDE_DIR})

QT4_WRAP_UI (UI_HEADERS ${UIS})
QT4_WRAP_CPP (MOC_SRCS ${DESKTOP_INCLUDES})

add_executable (moovie-desktop ${DESKTOP_SRC} ${MOC_SRCS} ${UI_HEADERS})
target_link_libraries (moovie-desktop ${QT_LIBRARIES} Qt4::QtGui Qt4::QtWebKit libmoovie ${CAIRO_LIBRARY_LOC} ${CAIROMM_LIBRARY_LOC})