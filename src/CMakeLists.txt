project(worker CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")

set(HEADERS
        graphs/GraphRepresentation.h
        graphs/SymmetricMatrix.h
        solvers/Solution.h
        solvers/Solver.h
        solvers/bnb/LittleMatrix.h
        solvers/bnb/BranchAndBound.h
        )
set(SOURCES
        graphs/GraphRepresentation.cpp
        graphs/SymmetricMatrix.cpp
        solvers/Solution.cpp
        solvers/Solver.cpp
        solvers/bnb/LittleMatrix.cpp
        solvers/bnb/BranchAndBound.cpp
        )

add_library(GR STATIC ${HEADERS} ${SOURCES})


add_executable(main main.cpp)

target_link_libraries(main GR)
