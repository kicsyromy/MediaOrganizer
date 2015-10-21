cmake_minimum_required(VERSION 2.6)
project(MediaOrganizer)
add_definitions(-DMO_LIB)

# Version number
set(MediaOrganizer_VERSION_MAJOR 0)
set(MediaOrganizer_VERSION_MINOR 1)
set(MediaOrganizer_VERSION_PATCH 0)

set(MediaOrganizer_PRIVATE_HEADERS "${PROJECT_SOURCE_DIR}/inc")
set(MediaOrganizer_PUBLIC_HEADERS  "${PROJECT_SOURCE_DIR}/pub")

# Generate configuration file with the proper version number
configure_file(
    "${PROJECT_SOURCE_DIR}/conf/mo_config.h.in"
    "${PROJECT_BINARY_DIR}/mo_config.h"
)

include("${MediaOrganizer_SOURCE_DIR}/cmake/ProjectConfig.cmake")

# Specify project include directories
include_directories("${PROJECT_SOURCE_DIR}/inc")
include_directories("${PROJECT_SOURCE_DIR}/pub")

# Add the build dir as include path for mo_config.h
include_directories("${PROJECT_BINARY_DIR}")

# Add path to external libraries
link_directories(${GOBJECT_LIBRARY_DIRS} ${GLIB2_LIBRARY_DIRS} ${LIBVLC_LIBRARY_DIRS})

# Define the source directories
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

# Specify the target
add_library(mo SHARED ${SRC_LIST} ${PROJECT_INFORMATION})

# Create aditional files with versioning
set_target_properties(mo PROPERTIES VERSION ${MediaOrganizer_VERSION_MAJOR}.${MediaOrganizer_VERSION_MINOR}.${MediaOrganizer_VERSION_PATCH} SOVERSION ${MediaOrganizer_VERSION_MAJOR})

# Se the apropriate compiler flags based on output from pkg-config
target_link_libraries(mo ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${LIBVLC_LIBRARIES})
target_include_directories(mo PUBLIC ${GOBJECT_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS} ${LIBVLC_INCLUDE_DIRS})
target_compile_options(mo PUBLIC ${GOBJECT_CFLAGS} ${GLIB_CFLAGS} ${LIBVLC_CFLAGS})

add_subdirectory(tests)
