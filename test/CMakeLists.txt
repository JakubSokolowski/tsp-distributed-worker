include_directories(GR)
set(TEST_SOURCES
        HelloTests.cpp
        graphs/AdjacencyMatrixTests.cpp)


add_executable(RunTests ${TEST_SOURCES})
target_link_libraries(RunTests gtest_main GR)

add_test(
        NAME
        unit
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/RunTests
)
