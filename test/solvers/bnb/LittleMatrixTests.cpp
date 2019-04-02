#include <gtest/gtest.h>
#include "../../../src/graphs/SymmetricMatrix.h"
#include "../../../src/solvers/bnb/LittleMatrix.h"

std::vector<std::vector<uint>> matrix_ =
{
        { INF, 10,  8,   9,   7 },
        { 10,  INF, 10,  5,   6 },
        { 8,   10,  INF, 8,   9 },
        { 9,   5,   8,   INF, 6 },
        { 7,   6,   9,   6,  INF }
};


TEST(LittleMatrixTests, LittleMatrixReduceAllRows) {
    auto matrix = LittleMatrix(matrix_);
    matrix.AssingIndices();
    
    std::vector<std::vector<uint>> reduced_matrix =
    {
        { INF,   3,  1,  2,   0 },
        { 5,   INF,  5,  0,   1 },
        { 0,   2,  INF,  0,   1 },
        { 4,   0,   3,   INF, 1 },
        { 1,   0,   3,   1,  INF }
    };
    
    auto result = matrix.ReduceAllRows();
    for (int i = 0; i < 5; i++)
        for (int j = 0; i < 5; i++)
        EXPECT_EQ(reduced_matrix[i][j], matrix(i + 1, j + 1));

    EXPECT_EQ(31, result);
}

TEST(LittleMatrixTests, LittleMatrixReduceColumn) {
    auto matrix = LittleMatrix(matrix_);

    std::vector<std::vector<uint>> reduced_matrix =
    {
        { INF, 10,  8,   9,   7 },
        { 3,  INF, 10,  5,   6 },
        { 1,   10,  INF, 8,   9 },
        { 2,   5,   8,   INF, 6 },
        { 0,   6,   9,   6,  INF }
    };
    matrix.AssingIndices();
    matrix.ReduceColumn(1);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; i < 5; i++) {
            EXPECT_EQ(reduced_matrix[i][j], matrix(i + 1, j + 1));
        }
    }

}

TEST(LittleMatrixTests, LittleMatrixReduceAllColumns){
    auto matrix = LittleMatrix(matrix_);
    matrix.AssingIndices();

    std::vector<std::vector<uint>> reduced_matrix =
    {
        { INF, 5,  0,   4,   1 },
        { 3,  INF, 2,   0,   0 },
        { 1,   5,  INF, 3,   2 },
        { 2,   0,   0,  INF, 0 },
        { 0,   1,   1,   1,  INF }
    };

    auto result = matrix.ReduceAllColumns();

    for (int i = 0; i < 5; i++)
        for (int j = 0; i < 5; i++)
        EXPECT_EQ(reduced_matrix[i][j], matrix(i +1 , j + 1));

    EXPECT_EQ(31, result);
}

TEST(LittleMatrixTests, LittleMatrixReduceMatrix) {
    auto matrix = LittleMatrix(matrix_);
    matrix.AssingIndices();

    std::vector<std::vector<uint>> reduced_matrix =
    {
        { INF,   3,  0,  2,   0 },
        { 5,   INF,  4,  0,   1 },
        { 0,   2,  INF, 0,   1 },
        { 4,   0,   2,   INF, 1 },
        { 1,   0,   2,   1,  INF }
    };

    auto result = matrix.ReduceMatrix();

    for (uint i = 0; i <  reduced_matrix.size(); i++)
        for (uint j = 0; i <  reduced_matrix.size(); i++) {
            EXPECT_EQ(reduced_matrix[i][j], matrix(i + 1, j + 1));
        }
    EXPECT_EQ(32, result);
}


TEST(LittleMatrixTests, LittleMatrixFindHighestPenaltyEdge) {
    auto matrix = LittleMatrix(matrix_);
    matrix.AssingIndices();

    matrix.ReduceMatrix();

    auto edge1 = Edge{};
    auto pos1 = Position();

    auto result = matrix.FindHighestPenaltyEdge(edge1,pos1);

    EXPECT_EQ(2, result);

    EXPECT_EQ(edge1.first, 1);
    EXPECT_EQ(edge1.second, 3);
    EXPECT_EQ(pos1.first, 1);
    EXPECT_EQ(pos1.second, 3);
}
