cmake_minimum_required(VERSION 3.4)
project(MooViE
        VERSION 1.0.0
        DESCRIPTION "Visualization tool for the results of multi-objective optimization"
        LANGUAGES CXX C)

# Set C++ language standard
set(CMAKE_CXX_STANDARD 14)

# Set module path for finding external modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# CMake build options
option(BUILD_GUI "Build QT Gui" ON)
option(BUILD_DOCUMENTATION "Build API documentation" OFF)
option(BUILD_TESTS "Build tests for the library" OFF)

if (BUILD_GUI)
  set(QT_VERSION QT6 CACHE STRING "Choose QT version")
  set_property(CACHE QT_VERSION PROPERTY STRINGS QT6 QT5)
else()
  unset(QT_VERSION CACHE)
endif()

# Set install destination variables
set(DEST_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(DEST_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(DEST_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include/moovie)
set(DEST_DOC_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/moovie)
set(DEST_DESKTOP_DIR ${CMAKE_INSTALL_PREFIX}/share/applications)
set(DEST_PIXMAP_DIR ${CMAKE_INSTALL_PREFIX}/share/pixmaps)
set(CMAKE_INSTALL_RPATH ${DEST_LIB_DIR})

# GNU debug flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fno-inline -fprofile-arcs -ftest-coverage --coverage")
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
                COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile)
        # Build reference manual using pdflatex
        add_custom_command(TARGET doc
                           COMMAND make pdf
                           WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs/build/latex)
        # Build html pages using sphinx
        add_custom_command(TARGET doc
                COMMAND make html
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs)
        add_custom_command(TARGET doc
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/docs/source/images
                ${PROJECT_SOURCE_DIR}/docs/build/html/_images)
        # Install html pages and reference manual
        install (FILES ${PROJECT_SOURCE_DIR}/docs/latex/refman.pdf DESTINATION ${DEST_DOC_DIR})

        # Install README file
        install (FILES README.md DESTINATION ${DEST_DOC_DIR})
    else(DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen and dot are needed to build the documentation. "
                "Either install Doxygen and dot or disable BUILD_DOCUMENTATION.")
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCUMENTATION)
