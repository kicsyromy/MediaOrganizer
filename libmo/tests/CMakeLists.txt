cmake_minimum_required(VERSION 2.8)
project(MediaOrganizer_Tests)
add_definitions(-DTEST_DATA_PATH=\"${MediaOrganizer_Tests_SOURCE_DIR}/data/\")

if(TEST_VIDEO_PLAYER)
    add_definitions(-DTEST_VIDEO_PLAYER)
endif(TEST_VIDEO_PLAYER)

if(TEST_FILE_BROWSER)
    add_definitions(-DTEST_FILE_BROWSER)
endif(TEST_FILE_BROWSER)

aux_source_directory("${MediaOrganizer_SOURCE_DIR}/tests" TST_SRC_LIST)
add_executable(test_libmo ${TST_SRC_LIST} ${PROJECT_INFORMATION})
target_link_libraries(test_libmo ${GOBJECT_LIBRARIES} ${GLIB2_LIBRARIES} ${LIBVLC_LIBRARIES} ${LIBMO})
