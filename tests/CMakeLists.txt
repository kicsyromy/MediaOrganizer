cmake_minimum_required(VERSION 2.6)
project(MediaOrganizer_Tests)
add_definitions(-DTEST_DATA_PATH=\"${MediaOrganizer_Tests_SOURCE_DIR}/data\")

aux_source_directory("${MediaOrganizer_SOURCE_DIR}/tests" TST_SRC_LIST)

add_executable(test_libmo "${TST_SRC_LIST}" ${PROJECT_INFORMATION})

target_link_libraries(test_libmo ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${LIBVLC_LIBRARIES} ${LIBMO})
target_include_directories(test_libmo PUBLIC
            ${GOBJECT_INCLUDE_DIRS}
            ${GLIB_INCLUDE_DIRS}
            ${LIBVLC_INCLUDE_DIRS}
            ${MediaOrganizer_PRIVATE_HEADERS}
            ${MediaOrganizer_PUBLIC_HEADERS}
)

target_compile_options(test_libmo PUBLIC ${GOBJECT_CFLAGS} ${GLIB_CFLAGS} ${LIBVLC_CFLAGS})
