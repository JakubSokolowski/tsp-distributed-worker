#ifndef TSP_SYMMETRIC_MATRIX_H
#define TSP_SYMMETRIC_MATRIX_H

#include <nlohmann/json.hpp>
#include "GraphRepresentation.h"

using json = nlohmann::json;
class SymmetricMatrix :
        public GraphRepresentation
{
public:
    SymmetricMatrix();

    explicit SymmetricMatrix(uint vertices_num);
    explicit SymmetricMatrix(const std::vector<Vertex> &coordinates);
    explicit SymmetricMatrix(const Matrix &matrix);

    ~SymmetricMatrix() override;


    void AddEdge(uint source, uint destination, uint cost) override;
    bool IsConnected(uint source, uint destination) const override;
    uint GetWeight(uint source, uint destination) const override;
    uint GetNumOfEdges() const override;
    uint GetNumOfVertices() const override;
    std::string GetGraphInfo()const override;
    static SymmetricMatrix FromJson(std::string json_str);
    static SymmetricMatrix FromJson(const json &json_obj);

    void Print() const override;

    std::vector<std::vector<uint>> GetMatrix();

protected:
    Matrix adjacency_matrix_;

};

#endif //TSP_SYMMETRIC_MATRIX_H
