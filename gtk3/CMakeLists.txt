cmake_minimum_required(VERSION 2.8)
project(MediaOrganizer-GTK3 C)

list(APPEND CMAKE_MODULE_PATH ${MediaOrganizer-GTK3_SOURCE_DIR}/cmake)

find_package(Vala REQUIRED)
find_package(PkgConfig)

pkg_search_module(LIBMO REQUIRED libmo>=0.1.0)
pkg_search_module(GTK3  REQUIRED gtk+-3.0>=3.15)
add_definitions(${LIBMO_CFLAGS} ${GTK3_CFLAGS})
link_libraries(${LIBMO_LIBRARIES} ${GTK3_LIBRARIES})
link_directories(${LIBMO_LIBRARY_DIRS} ${GTK3_LIBRARY_DIRS})

include("${MediaOrganizer-GTK3_SOURCE_DIR}/cmake/UseVala.cmake")
vala_precompile(VALA_C
    src/main.vala
    src/main_window.vala
PACKAGES
    gtk+-3.0
CUSTOM_VAPIS
    ${CMAKE_SOURCE_DIR}/../libmo/conf/libmo.vapi
)

add_executable(MediaOrganizer ${VALA_C})
