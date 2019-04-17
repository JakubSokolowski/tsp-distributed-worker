project(worker CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.40.0 REQUIRED system)
find_package(Boost COMPONENTS asio)

ADD_SUBDIRECTORY(proto)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

set(HEADERS
        graphs/GraphRepresentation.h
        graphs/SymmetricMatrix.h
        solvers/Solution.h
        solvers/Solver.h
        solvers/bnb/LittleMatrix.h
        solvers/bnb/BranchAndBound.h
        socket/ConfigurationProvider.h
        socket/Client.h
        )
set(SOURCES
        graphs/GraphRepresentation.cpp
        graphs/SymmetricMatrix.cpp
        solvers/Solution.cpp
        solvers/Solver.cpp
        solvers/bnb/LittleMatrix.cpp
        solvers/bnb/BranchAndBound.cpp
        socket/ConfigurationProvider.cpp
        socket/Client.cpp )

add_library(GR STATIC ${HEADERS} ${SOURCES})


add_executable(main main.cpp)

target_link_libraries(main proto GR )
