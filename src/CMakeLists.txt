project(worker CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")

set(HEADERS
        graphs/GraphRepresentation.h
        graphs/SymmetricMatrix.h)
set(SOURCES
        graphs/GraphRepresentation.cpp
        graphs/SymmetricMatrix.cpp)

add_library(GR STATIC ${HEADERS} ${SOURCES})


add_executable(main main.cpp)

target_link_libraries(main GR)
