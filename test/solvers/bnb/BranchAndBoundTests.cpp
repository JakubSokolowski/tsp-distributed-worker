#include <gtest/gtest.h>
#include "../../../src/graphs/SymmetricMatrix.h"
#include "../../../src/solvers/bnb/LittleMatrix.h"
#include "../../../src/solvers/bnb/BranchAndBound.h"


TEST(BranchAndBound, LittleSymmetric5) {
    std::vector<std::vector<uint>> matrix =
    {
        { INF, 10,  8,   9,   7 },
        { 10,  INF, 10,  5,   6 },
        { 8,   10,  INF, 8,   9 },
        { 9,   5,   8,   INF, 6 },
        { 7,   6,   9,   6,  INF }
    };

    auto graph = SymmetricMatrix(matrix);
    auto solver = BranchAndBound();
    auto result = solver.Solve(graph);
    EXPECT_EQ(34, result.tour_cost);
    auto expected_path = std::vector<uint>{ 1,3,4,2,5,1 };
    auto actual_path = result.tour;
    for (uint i = 0; i < actual_path.size() - 1; i++)
        EXPECT_EQ(expected_path[i], actual_path[i]);
}