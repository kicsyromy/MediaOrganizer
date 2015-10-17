cmake_minimum_required(VERSION 2.6)
project(MediaOrganizer)

# Version number
set(MediaOrganizer_VERSION_MAJOR 0)
set(MediaOrganizer_VERSION_MINOR 1)
set(MediaOrganizer_VERSION_PATCH 0)

# Generate configuration file with the proper version number
configure_file(
    "${PROJECT_SOURCE_DIR}/conf/mo_config.h.in"
    "${PROJECT_BINARY_DIR}/mo_config.h"
)

# Use pkg-config
find_package(PkgConfig)
pkg_search_module(GOBJECT REQUIRED gobject-2.0)
pkg_search_module(GLIB2   REQUIRED glib-2.0)
pkg_search_module(LIBVLC  REQUIRED libvlc)

# Specify project include directories
include_directories("${PROJECT_SOURCE_DIR}/inc")
include_directories("${PROJECT_SOURCE_DIR}/pub")

# Add the build dir as include path for mo_config.h
include_directories("${PROJECT_BINARY_DIR}")

# Define the source directories
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

# Specify the target
add_library(mo SHARED ${SRC_LIST})

# Create aditional files with versioning
set_target_properties(mo PROPERTIES VERSION ${MediaOrganizer_VERSION_MAJOR}.${MediaOrganizer_VERSION_MINOR}.${MediaOrganizer_VERSION_PATCH} SOVERSION ${MediaOrganizer_VERSION_MAJOR})

# Se the apropriate compiler flags based on output from pkg-config
target_link_libraries(mo ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${LIBVLC_LIBRARIES})
target_include_directories(mo PUBLIC ${GOBJECT_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS} ${LIBVLC_INCLUDE_DIRS})
target_compile_options(mo PUBLIC ${GOBJECT_CFLAGS_OTHER} ${GLIB_CFLAGS_OTHER} ${LIBVLC_CFLAGS_OTHER})
