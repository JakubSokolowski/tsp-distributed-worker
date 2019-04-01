#ifndef TSP_GRAPH_REPRESENTATION
#define TSP_GRAPH_REPRESENTATION

#define NINT(a) ((a) >= 0.0 ? (int)((a)+0.5) : (int)((a)-0.5))

#include <string>
#include <vector>
#include <cmath>
#include <limits>

using uint = unsigned int;
using density = double;
using Matrix = std::vector<std::vector<uint>>;

constexpr uint INF = std::numeric_limits<uint>::max();

struct Vertex
{
    uint x;
    uint y;
    uint id;
};

class  GraphRepresentation {
public:
    GraphRepresentation() = default;
    explicit GraphRepresentation(const std::vector<Vertex> &coordinates);
    virtual ~GraphRepresentation() = default;

    virtual void AddEdge(uint source, uint destination, uint cost) = 0;

    virtual bool IsConnected(uint source, uint destination) const = 0;
    virtual uint GetWeight(uint source, uint destination) const = 0;
    virtual uint GetNumOfEdges() const = 0;
    virtual uint GetNumOfVertices() const = 0;
    virtual std::string GetGraphInfo() const = 0;
    virtual void Print() const = 0;
    virtual uint GetTourCost(const std::vector<uint> &tour) const;

protected:
    std::vector<Vertex> coordinates_;
    uint edges_num_ = 0;

    Matrix AllocateSquareMatrix(uint matrix_size);
    void ConvertCoordinatesToWeights(const std::vector<Vertex> &coordinates);
    uint GetEuclideanDistance(const Vertex &source, const Vertex &destination);
};

#endif //TSP_GRAPHREPRESENTATION_H
