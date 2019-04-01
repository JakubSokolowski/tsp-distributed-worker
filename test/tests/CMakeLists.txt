include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(Graphs)
set(TEST_SOURCES
        HelloTests.cpp
        )
add_executable(RunTests ${TEST_SOURCES})
target_link_libraries(RunTests gtest gtest_main)