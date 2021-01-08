# General settings
cmake_minimum_required (VERSION 3.4)
project (MooViE)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set (CMAKE_CXX_STANDARD 11)

include(CheckIncludeFile)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

option(BUILD_GUI "Build a QT Gui" ON)
option(BUILD_DOCUMENTATION "Build API documentation" OFF)
option(BUILD_TESTS "Build tests for the library" OFF)

# Set code location variables
set (MOOVIE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (MOOVIE_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set (DESKTOP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/desktop)
set (DESKTOP_SRC_DIR ${PROJECT_SOURCE_DIR}/src/desktop)
set (DESKTOP_UI_DIR ${PROJECT_SOURCE_DIR}/ui)

# Set install destination variables
set (DEST_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set (DEST_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set (DEST_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/moovie)
set (DEST_DOC_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/moovie)
set (DEST_DESKTOP_DIR ${CMAKE_INSTALL_PREFIX}/share/applications)
set (DEST_PIXMAP_DIR ${CMAKE_INSTALL_PREFIX}/share/pixmaps)
set(CMAKE_INSTALL_RPATH ${DEST_LIB_DIR})

# Find external libraries
# - Cairomm (C++ SVG painting using Cairo)
# - Qt5 (gui)
# - Doxygen (documentation generation)
find_package (Cairomm REQUIRED)
if (BUILD_GUI)
    find_package (Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineWidgets REQUIRED)
endif()
check_include_file("unistd.h"  HAVE_UNISTD_H)
configure_file(moovie_config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/moovie_config.h)
if (BUILD_DOCUMENTATION)
    find_package (Doxygen REQUIRED dot)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen and dot are needed to build the documentation. Either install Doxygen and dot or disable BUILD_DOCUMENTATION.")
    endif()
endif()

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


include_directories (
        ${MOOVIE_INCLUDE_DIR} # Project includes
        ${MOOVIE_INCLUDE_DIR}/thirdparty/tclap # Headers of TCLAP for command line parsing
        ${CAIROMM_INCLUDE_DIRS}) # Cairomm, Cairo, SigC++ and Freetype includes

#MSVC stuff
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    add_definitions(-D_USE_MATH_DEFINES)
    add_compile_options("/Za")
endif()

# Build MooViE library
add_library (libmoovie SHARED ${MOOVIE_SRC})
include(GenerateExportHeader)
generate_export_header(libmoovie)
set_target_properties (libmoovie PROPERTIES OUTPUT_NAME moovie)
target_link_libraries (libmoovie PUBLIC  ${CAIROMM_LIBRARIES})


# Build MooViE executable
add_executable (moovie ${MOOVIE_SRC_DIR}/moovie.cpp)
add_dependencies (moovie libmoovie)
target_link_libraries (moovie PUBLIC libmoovie)

include_directories(${PROJECT_BINARY_DIR})

if (BUILD_GUI)
    # Build Qt5 application
    include_directories (${CMAKE_BINARY_DIR} ${DESKTOP_INCLUDE_DIR})

    QT5_WRAP_UI (UI_HEADERS ${UIS})
    QT5_WRAP_CPP (MOC_SRCS ${DESKTOP_INCLUDES})

    add_executable (moovie-desktop ${DESKTOP_SRC} ${MOC_SRCS} ${UI_HEADERS})
    add_dependencies(moovie-desktop libmoovie)
    target_link_libraries (moovie-desktop Qt5::Core Qt5::Gui Qt5::Widgets Qt5::WebEngine Qt5::WebEngineWidgets libmoovie)
endif()


# Installation
install (FILES ${MOOVIE_INCLUDES} ${PROJECT_BINARY_DIR}/libmoovie_export.h ${CMAKE_CURRENT_BINARY_DIR}/moovie_config.h DESTINATION ${DEST_INCLUDE_DIR})
install (TARGETS libmoovie DESTINATION ${DEST_LIB_DIR})
install (TARGETS moovie DESTINATION ${DEST_BIN_DIR})
if (BUILD_GUI)
    file(WRITE ${PROJECT_BINARY_DIR}/moovie.desktop "[Desktop Entry]
Name=MooViE
Exec=${DEST_BIN_DIR}/moovie-desktop
Icon=${DEST_PIXMAP_DIR}/moovie.png
Categories=Science;DataVisualization;
Terminal=false
Type=Application\n")
    install (TARGETS moovie-desktop DESTINATION ${DEST_BIN_DIR})
    install (FILES ${PROJECT_BINARY_DIR}/moovie.desktop DESTINATION ${DEST_DESKTOP_DIR})
    install (FILES moovie.png DESTINATION ${DEST_PIXMAP_DIR})
endif()
install (DIRECTORY ${MOOVIE_DOC_DIR} DESTINATION ${DEST_DOC_DIR})
install (FILES README.md DESTINATION ${DEST_DOC_DIR})


# Build and install documentation
if (BUILD_DOCUMENTATION)
    if (DOXYGEN_FOUND)
        configure_file (${PROJECT_SOURCE_DIR}/Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)
        add_custom_target(doc
                          ALL
                          COMMENT "Generating API documentation with Doxygen" VERBATIM)
        add_custom_command (
                            TARGET doc
                            COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
                            OUTPUTS ${PROJECT_BINARY_DIR}/doc/man/man3/moovie.3)
        # Build reference manual using pdflatex
        add_custom_command(
                           TARGET doc
                           COMMAND make pdf
                           WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc/latex)
        # Install html pages and reference manual
        install (DIRECTORY ${PROJECT_BINARY_DIR}/doc/html DESTINATION ${DEST_DOC_DIR})
        install (FILES ${PROJECT_BINARY_DIR}/doc/latex/refman.pdf DESTINATION ${DEST_DOC_DIR})
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCUMENTATION)


# Add test subdirectory
if (BUILD_TESTS)
    include(CTest)
    add_subdirectory(test)
endif(BUILD_TESTS)
