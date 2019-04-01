#include "SymmetricMatrix.h"

using std::vector;

SymmetricMatrix::SymmetricMatrix()
        : adjacency_matrix_(AllocateSquareMatrix(5))
{ }

SymmetricMatrix::SymmetricMatrix(uint vertices_num)
        : adjacency_matrix_(AllocateSquareMatrix(vertices_num))
{ }


SymmetricMatrix::SymmetricMatrix(const vector<Vertex> &coordinates) 
        : GraphRepresentation(coordinates)
        , adjacency_matrix_(AllocateSquareMatrix((uint)coordinates.size()))
{
    ConvertCoordinatesToWeights(coordinates_);
}

SymmetricMatrix::SymmetricMatrix(const Matrix &matrix)
        : adjacency_matrix_(matrix)
{}

SymmetricMatrix::~SymmetricMatrix() = default;

void SymmetricMatrix::AddEdge(uint source, uint destination, uint cost) {
    if(!IsConnected(source, destination)) {
        adjacency_matrix_[source][destination] = cost;
        adjacency_matrix_[destination][source] = cost;
        ++edges_num_;
    }
}


bool SymmetricMatrix::IsConnected(uint source, uint destination) const {
    return adjacency_matrix_[source][destination] != INF;
}

uint SymmetricMatrix::GetWeight(uint source, uint destination) const {
    return adjacency_matrix_[source][destination];
}

uint SymmetricMatrix::GetNumOfEdges() const {
    return edges_num_;
}

uint SymmetricMatrix::GetNumOfVertices() const {
    return static_cast<uint>(adjacency_matrix_.size());
}

std::string SymmetricMatrix::GetGraphInfo() const {
    return "info";
}

void SymmetricMatrix::Print() const {

}

vector<vector<uint>> SymmetricMatrix::GetMatrix() {
    return adjacency_matrix_;
}
