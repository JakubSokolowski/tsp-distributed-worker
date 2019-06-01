#include "GraphRepresentation.h"

using std::vector;

uint GraphRepresentation::GetTourCost(const vector<uint> &tour) const {
    uint result = 0;
    auto ver = GetNumOfVertices();
    for (uint i = 0; i < ver; ++i)
        result += GetWeight(tour[i] - 1, tour[i + 1] - 1);
    return result;
}

Matrix GraphRepresentation::AllocateSquareMatrix(uint matrix_size) {
    const auto vec = vector<uint>(matrix_size, std::numeric_limits<uint>::max());
    return Matrix(matrix_size, vec);
}

void GraphRepresentation::ConvertCoordinatesToWeights(const vector<Vertex> &coordinates) {
    uint destination_vertex = 1;
    for (uint i = 0; i < coordinates.size() - 1; i++) {
        for (uint j = destination_vertex; j < coordinates.size(); j++) {
            edges_num_++;
            uint edge_weight = GetEuclideanDistance(coordinates[i], coordinates[j]);
            AddEdge(i, j, edge_weight);
        }
        destination_vertex++;
    }

}

uint GraphRepresentation::GetEuclideanDistance(const Vertex &source, const Vertex &destination) {
    int X = source.x - destination.x;
    int Y = source.y - destination.y;
    return static_cast<uint>(NINT(sqrt(pow(X, 2) + pow(Y, 2))));
}

GraphRepresentation::GraphRepresentation(const std::vector<Vertex> &coordinates)
        : coordinates_(coordinates)
{ }
