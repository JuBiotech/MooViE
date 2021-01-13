# Try to find the Cairomm-1.0 library
#
# Following are set afterwards:
# CAIROMM_FOUND
# CAIROMM_INCLUDE_DIR
# CAIROMM_LIBRARY_LOC
# CAIROMM_LIBRARIES
# CAIROMM_CONFIG_DIR

include(FindPackageHandleStandardArgs)

find_package(Cairo REQUIRED)
find_package(Freetype REQUIRED)

# As of now, there are 3 ABI versions of cairomm 1.0, 1.14 and 1.16
# all of them have different .pc names, so we check them sequentially
# warning! although very simmilar the ABI versions do not coincide with the software version
find_package(PkgConfig)
pkg_check_modules(PC_CAIROMM QUIET cairomm-1.0)
if (PC_CAIROMM_FOUND)
    set(CAIROMM_ABI "1.0")
else (NOT PC_CAIROMM_FOUND)
    pkg_check_modules(PC_CAIROMM QUIET cairomm-1.14)
    set(CAIROMM_ABI "1.14")
endif()
# still not found -> neither 1.0 nor 1.14
if (NOT PC_CAIROMM_FOUND)
    pkg_check_modules(PC_CAIROMM QUIET cairomm-1.16)
    set(CAIROMM_ABI "1.16")
endif()


find_path(CAIROMM_INCLUDE_DIR
        NAMES cairomm/cairomm.h
        HINTS ${PC_CAIROMM_INCLUDEDIR}
              ${PC_CAIROMM_INCLUDE_DIRS}
        REQUIRED)

find_path(CAIROMM_CONFIG_DIR 
        NAMES cairommconfig.h
        HINTS ${PC_CAIROMM_INCLUDEDIR}
              ${PC_CAIROMM_INCLUDE_DIRS}
        REQUIRED)
        
if (CAIROMM_CONFIG_DIR)
    if (EXISTS "${CAIROMM_CONFIG_DIR}/cairommconfig.h")
        file(READ "${CAIROMM_CONFIG_DIR}/cairommconfig.h" CAIROMM_CONFIG_CONTENT)

        string(REGEX MATCH "#define +CAIROMM_MAJOR_VERSION +([0-9]+)" _dummy "${CAIROMM_CONFIG_CONTENT}")
        set(CAIROMM_MAJOR_VERSION "${CMAKE_MATCH_1}")

        string(REGEX MATCH "#define +CAIROMM_MINOR_VERSION +([0-9]+)" _dummy "${CAIROMM_CONFIG_CONTENT}")
        set(CAIROMM_MINOR_VERSION "${CMAKE_MATCH_1}")

        string(REGEX MATCH "#define +CAIROMM_MICRO_VERSION +([0-9]+)" _dummy "${CAIROMM_CONFIG_CONTENT}")
        set(CAIROMM_MICRO_VERSION "${CMAKE_MATCH_1}")

        set(CAIROMM_VERSION "${CAIROMM_MAJOR_VERSION}.${CAIROMM_MINOR_VERSION}.${CAIROMM_MICRO_VERSION}")
    endif ()
endif ()

find_library(CAIROMM_LIBRARY
    NAMES cairomm-${CAIROMM_ABI}
    HINTS ${PC_CAIROMM_LIBDIR}
          ${PC_CAIROMM_LIBRARY_DIRS}
    REQUIRED)
        
# TODO Unsure if the version is correct
# TODO this VERSION_GREATER_EQUAL is the reason we require cmake 3.7 instead of 3.4
if (CAIROMM_VERSION VERSION_GREATER_EQUAL "1.14.0")
    SET(REQ_SIGCPP_ABI "3.0")
    set (CMAKE_CXX_STANDARD 17)
else()
    SET(REQ_SIGCPP_ABI "2.0")
endif()

find_package(SigC++ ${REQ_SIGCPP_ABI} REQUIRED)
set(CAIROMM_INCLUDE_DIRS ${CAIROMM_INCLUDE_DIR} ${CAIROMM_CONFIG_DIR} ${CAIRO_INCLUDE_DIRS} ${SIGCPP_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})
set(CAIROMM_LIBRARIES ${CAIROMM_LIBRARY} ${CAIRO_LIBRARIES})

find_package_handle_standard_args(Cairomm REQUIRED_VARS CAIROMM_LIBRARY CAIROMM_INCLUDE_DIR CAIROMM_CONFIG_DIR)
