cmake_minimum_required(VERSION 2.6)
project(MediaOrganizer)
add_definitions(-DMO_LIB)

# Version number
set(MediaOrganizer_VERSION_MAJOR 0)
set(MediaOrganizer_VERSION_MINOR 1)
set(MediaOrganizer_VERSION_PATCH 0)

# Generate configuration file with the proper version number
configure_file(
    "${PROJECT_SOURCE_DIR}/conf/mo_config.h.in"
    "${PROJECT_BINARY_DIR}/mo_config.h"
)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	# Use pkg-config
	find_package(PkgConfig)
	pkg_search_module(GOBJECT REQUIRED gobject-2.0)
	pkg_search_module(GLIB2   REQUIRED glib-2.0)
	pkg_search_module(LIBVLC  REQUIRED libvlc)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(TargetArch_DIR 		"${PROJECT_SOURCE_DIR}/cmake")
	set(ProductVersion_DIR  "${PROJECT_SOURCE_DIR}/cmake")
	
	find_package(TargetArch)
	target_architecture(ARCH)
	IF(${ARCH} MATCHES "x86_64")
		set(LIB_PATH "${PROJECT_SOURCE_DIR}/windows/lib/x64")
	ELSE(${ARCH} MATCHES "x86_64")
		set(LIB_PATH "${PROJECT_SOURCE_DIR}/windows/lib/win32")
	ENDIF(${ARCH} MATCHES "x86_64")

	find_package(ProductVersion)
	generate_product_version(
		PROJECT_INFORMATION
		NAME "Media Organizer"
		ICON "${PROJECT_SOURCE_DIR}/windows/project.ico"
		VERSION_MAJOR ${MediaOrganizer_VERSION_MAJOR}
		VERSION_MINOR ${MediaOrganizer_VERSION_MINOR}
		VERSION_PATCH ${MediaOrganizer_VERSION_PATCH}
		VERSION_REVISION 0
		COMPANY_NAME "Romeo Calota"
	)

	set(GOBJECT_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/windows/include/gio-win32-2.0")
	set(GLIB_INCLUDE_DIRS    "${PROJECT_SOURCE_DIR}/windows/include/glib-2.0")
	set(LIBVLC_INCLUDE_DIRS  "${PROJECT_SOURCE_DIR}/windows/include")
	
	set(GOBJECT_LIBRARIES "${LIB_PATH}/gobject-2.0.lib")
	set(GLIB2_LIBRARIES   "${LIB_PATH}/glib-2.0.lib")
	set(LIBVLC_LIBRARIES  "${LIB_PATH}/libvlc.lib")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# Specify project include directories
include_directories("${PROJECT_SOURCE_DIR}/inc")
include_directories("${PROJECT_SOURCE_DIR}/pub")

# Add the build dir as include path for mo_config.h
include_directories("${PROJECT_BINARY_DIR}")

# Define the source directories
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

# Specify the target
add_library(mo SHARED ${SRC_LIST} ${PROJECT_INFORMATION})

# Create aditional files with versioning
set_target_properties(mo PROPERTIES VERSION ${MediaOrganizer_VERSION_MAJOR}.${MediaOrganizer_VERSION_MINOR}.${MediaOrganizer_VERSION_PATCH} SOVERSION ${MediaOrganizer_VERSION_MAJOR})

# Se the apropriate compiler flags based on output from pkg-config
target_link_libraries(mo ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${LIBVLC_LIBRARIES})
target_include_directories(mo PUBLIC ${GOBJECT_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS} ${LIBVLC_INCLUDE_DIRS})
target_compile_options(mo PUBLIC ${GOBJECT_CFLAGS_OTHER} ${GLIB_CFLAGS_OTHER} ${LIBVLC_CFLAGS_OTHER})
