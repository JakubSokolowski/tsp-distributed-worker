include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(GR)
set(TEST_SOURCES
        HelloTests.cpp
        graphs/AdjacencyMatrixTests.cpp)


add_executable(RunTests ${TEST_SOURCES})
target_link_libraries(RunTests gtest gtest_main GR)

if (COVERAGE)
    target_compile_options(RunTests PRIVATE --coverage)
    target_link_libraries(RunTests PRIVATE --coverage)
endif()