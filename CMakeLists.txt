# General settings
cmake_minimum_required (VERSION 3.4)
project (MooViE)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set (CMAKE_CXX_STANDARD 11)

include(CheckIncludeFile)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# CMake build options
option(BUILD_GUI "Build a QT Gui" ON)
option(BUILD_DOCUMENTATION "Build API documentation" OFF)
option(BUILD_TESTS "Build tests for the library" OFF)

# Set install destination variables
set(DEST_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(DEST_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(DEST_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/moovie)
set(DEST_DOC_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/moovie)
set(DEST_DESKTOP_DIR ${CMAKE_INSTALL_PREFIX}/share/applications)
set(DEST_PIXMAP_DIR ${CMAKE_INSTALL_PREFIX}/share/pixmaps)
set(CMAKE_INSTALL_RPATH ${DEST_LIB_DIR})

# Find external libraries
# - Cairomm (C++ SVG painting using Cairo)
# - Qt5 (gui)
find_package(Cairomm REQUIRED)
include_directories(${CAIROMM_INCLUDE_DIRS})
if (BUILD_GUI)
    find_package(Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineWidgets REQUIRED)
endif()
check_include_file("unistd.h"  HAVE_UNISTD_H)
configure_file(moovie_config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/moovie_config.h)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(${BUILD_DOCUMENTATION} ON)
    set(${BUILD_TESTS} ON)
endif()

# MSVC options
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    add_definitions(-D_USE_MATH_DEFINES)
    add_compile_options("/Za")
endif()

# MooViE sources
add_subdirectory(src/main)

# Test sources
if (BUILD_TESTS)
    include(CTest)
    add_subdirectory(src/test)
endif(BUILD_TESTS)

# Documentation
if (BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED dot)

    if (DOXYGEN_FOUND)
        configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)
        add_custom_target(doc
                ALL
                COMMENT "Generating API documentation with Doxygen" VERBATIM)
        add_custom_command(TARGET doc
                COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
                OUTPUTS ${PROJECT_BINARY_DIR}/doc/man/man3/moovie.3)
        # Build reference manual using pdflatex
        add_custom_command(TARGET doc
                           COMMAND make pdf
                           WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc/latex)
        # Install html pages and reference manual
        install (DIRECTORY ${PROJECT_BINARY_DIR}/doc/html DESTINATION ${DEST_DOC_DIR})
        install (FILES ${PROJECT_BINARY_DIR}/doc/latex/refman.pdf DESTINATION ${DEST_DOC_DIR})

        # Install README file
        install (FILES README.md DESTINATION ${DEST_DOC_DIR})
    else(DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen and dot are needed to build the documentation. "
                "Either install Doxygen and dot or disable BUILD_DOCUMENTATION.")
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCUMENTATION)