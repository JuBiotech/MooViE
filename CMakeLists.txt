# General settings
cmake_minimum_required (VERSION 3.1)
project (MooViE)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set (CMAKE_CXX_STANDARD 11)

# Set code location variables
set (MOOVIE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (MOOVIE_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set (MOOVIE_DOC_DIR ${PROJECT_SOURCE_DIR}/doc)
set (DESKTOP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/desktop)
set (DESKTOP_SRC_DIR ${PROJECT_SOURCE_DIR}/src/desktop)
set (DESKTOP_UI_DIR ${PROJECT_SOURCE_DIR}/ui)

# Set install destination variables
set (DEST_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set (DEST_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set (DEST_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/moovie)
set (DEST_DOC_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/moovie)
set (DEST_DESKTOP_DIR /usr/share/applications)
set (DEST_PIXMAP_DIR /usr/share/pixmaps)

# Find important libraries
# Moovie uses Cairomm-1.0, which depends on
# - Cairo, which depends on
#   - freetype2
#   - sigc++-2.0
find_package (freetype2 REQUIRED)
find_package (sigc++-2.0 REQUIRED)
find_package (cairo REQUIRED)
find_package (cairomm-1.0 REQUIRED)
find_package (Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineWidgets REQUIRED)

# Structure files
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

set (DESKTOP_INCLUDES
	${DESKTOP_INCLUDE_DIR}/MainWindow.h
	${DESKTOP_INCLUDE_DIR}/IOList.h
	${DESKTOP_INCLUDE_DIR}/IOListWidget.h
	${DESKTOP_INCLUDE_DIR}/ConfigurationDialog.h
	${DESKTOP_INCLUDE_DIR}/ConfIntWidget.h
	${DESKTOP_INCLUDE_DIR}/ConfDoubleWidget.h
	${DESKTOP_INCLUDE_DIR}/ConfStringWidget.h
	${DESKTOP_INCLUDE_DIR}/MooViEView.h
)

set (DESKTOP_SRC
	${DESKTOP_SRC_DIR}/moovie-desktop.cpp
	${DESKTOP_SRC_DIR}/MainWindow.cpp
	${DESKTOP_SRC_DIR}/IOList.cpp
	${DESKTOP_SRC_DIR}/IOListWidget.cpp
	${DESKTOP_SRC_DIR}/ConfigurationDialog.cpp
	${DESKTOP_SRC_DIR}/ConfIntWidget.cpp
	${DESKTOP_SRC_DIR}/ConfDoubleWidget.cpp
	${DESKTOP_SRC_DIR}/ConfStringWidget.cpp
	${DESKTOP_SRC_DIR}/MooViEView.cpp
)

set (UIS
	${DESKTOP_UI_DIR}/MainWindow.ui
	${DESKTOP_UI_DIR}/IOListWidget.ui
	${DESKTOP_UI_DIR}/ConfigurationDialog.ui
	${DESKTOP_UI_DIR}/ConfIntWidget.ui
	${DESKTOP_UI_DIR}/ConfDoubleWidget.ui
	${DESKTOP_UI_DIR}/ConfStringWidget.ui
)


# Add includes and linking
include_directories (${MOOVIE_INCLUDE_DIR} ${MOOVIE_INCLUDE_DIR}/thirdparty/tclap ${FREETYPE2_INCLUDE_DIR} ${SIGCPP_CONFIG_DIR} ${SIGCPP_INCLUDE_DIR} ${CAIRO_INCLUDE_DIR} ${CAIROMM_CONFIG_DIR} ${CAIROMM_INCLUDE_DIR})


# Build MooViE library
add_library (libmoovie STATIC "")
target_sources (libmoovie PUBLIC ${MOOVIE_SRC})
set_target_properties (libmoovie PROPERTIES OUTPUT_NAME moovie)


# Build MooViE executable
add_executable (moovie ${MOOVIE_SRC_DIR}/moovie.cpp)
add_dependencies (moovie libmoovie)
target_link_libraries (moovie PUBLIC libmoovie ${CAIRO_LIBRARY_LOC} ${CAIROMM_LIBRARY_LOC})


# Build Qt5 application
include_directories (${CMAKE_BINARY_DIR} ${DESKTOP_INCLUDE_DIR})

QT5_WRAP_UI (UI_HEADERS ${UIS})
QT5_WRAP_CPP (MOC_SRCS ${DESKTOP_INCLUDES})

add_executable (moovie-desktop ${DESKTOP_SRC} ${MOC_SRCS} ${UI_HEADERS})
target_link_libraries (moovie-desktop Qt5::Core Qt5::Gui Qt5::Widgets Qt5::WebEngine Qt5::WebEngineWidgets libmoovie ${CAIRO_LIBRARY_LOC} ${CAIROMM_LIBRARY_LOC})


# Installation
install (FILES ${MOOVIE_INCLUDES} DESTINATION ${DEST_INCLUDE_DIR})
install (TARGETS libmoovie DESTINATION ${DEST_LIB_DIR})
install (TARGETS moovie DESTINATION ${DEST_BIN_DIR})
install (TARGETS moovie-desktop DESTINATION ${DEST_BIN_DIR})
install (DIRECTORY ${MOOVIE_DOC_DIR} DESTINATION ${DEST_DOC_DIR})
install (FILES README.md DESTINATION ${DEST_DOC_DIR})
install (FILES moovie.desktop DESTINATION ${DEST_DESKTOP_DIR})
install (FILES moovie.png DESTINATION ${DEST_PIXMAP_DIR})
