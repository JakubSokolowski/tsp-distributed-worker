#ifndef TSP_GRAPHPARSER_H
#define TSP_GRAPHPARSER_H


#include <fstream>
#include <type_traits>
#include <iterator>
#include <vector>
#include <limits>
#include <sstream>

#include "GraphRepresentation.h"
using Coordinates = std::vector<Vertex>;

class GraphParser {
public:
    Coordinates ReadCoordinates(std::fstream &stream);

    Matrix ReadMatrix(std::fstream &stream);

    Matrix ReadFullMatrix(std::fstream &stream);

    template <typename Graph>
    Graph Parse(const std::string &filename);
};


#endif //TSP_GRAPHPARSER_H
