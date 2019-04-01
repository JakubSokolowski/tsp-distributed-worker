#include <gtest/gtest.h>
#include "../../../src/graphs/SymmetricMatrix.h"


TEST(SymmetricMatrix, SymmetricMatrixConstructorTest) {
    auto matrix = SymmetricMatrix(5);
    EXPECT_EQ(uint(5), matrix.GetNumOfVertices());
    EXPECT_EQ(uint(0), matrix.GetNumOfEdges());
    EXPECT_EQ(std::numeric_limits<uint>::max(), matrix.GetWeight(0, 0));
    EXPECT_EQ(std::numeric_limits<uint>::max(), matrix.GetWeight(4, 4));
}

TEST(SymmetricMatrix, SymmetricMatrixAddEdge) {
    auto matrix = SymmetricMatrix(5);
    EXPECT_EQ(uint(5), matrix.GetNumOfVertices());
    EXPECT_EQ(uint(0), matrix.GetNumOfEdges());
    EXPECT_EQ(std::numeric_limits<uint>::max(), matrix.GetWeight(0, 0));
    EXPECT_EQ(std::numeric_limits<uint>::max(), matrix.GetWeight(4, 4));
}

TEST(SymmetricMatrix, AsymmetricMatrixAddEdge) {
    auto Graph = SymmetricMatrix(4);
    Graph.AddEdge(0, 1, 20);
    Graph.AddEdge(0, 2, 42);
    Graph.AddEdge(0, 3, 35);
    Graph.AddEdge(3, 2, 12);
    Graph.AddEdge(1, 3, 34);
    Graph.AddEdge(1, 2, 30);

    EXPECT_EQ(uint(4), Graph.GetNumOfVertices());
    EXPECT_EQ(uint(6), Graph.GetNumOfEdges());
    EXPECT_EQ(std::numeric_limits<uint>::max(), Graph.GetWeight(0, 0));
    EXPECT_EQ(std::numeric_limits<uint>::max(), Graph.GetWeight(3, 3));
    EXPECT_EQ(35, Graph.GetWeight(0, 3));
    EXPECT_EQ(35, Graph.GetWeight(3, 0));
}



