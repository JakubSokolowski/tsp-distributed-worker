#include "GraphParser.h"

Coordinates GraphParser::ReadCoordinates(std::fstream &stream) {
    uint id;
    double x,y;
    auto coordinates = Coordinates();
    while(stream >> id >> x >> y)
        coordinates.push_back(Vertex{(uint)x, uint(y) ,id});
    return coordinates;
}

Matrix GraphParser::ReadMatrix(std::fstream &stream) {
    std::string line;
    auto matrix = Matrix{};
    while (std::getline(stream, line)) {
        std::istringstream is(line);
        auto vec = std::vector<uint>(std::istream_iterator<uint>(is), std::istream_iterator<uint>());
        matrix.push_back(vec);
    }
    for (uint i = 0; i < matrix.size(); i++)
        matrix[i][i] = INF;

    return matrix;
}

Matrix GraphParser::ReadFullMatrix(std::fstream &stream) {
    auto raw_vec = std::vector<uint>(std::istream_iterator<uint>(stream), std::istream_iterator<uint>());
    auto chunk = (uint)sqrt(raw_vec.size());
    uint start = 0;
    auto matrix = Matrix{};

    for (uint i = 0; i < chunk; i++)  {
        auto vec = std::vector<uint>(raw_vec.begin() + start, raw_vec.begin() + start + chunk);
        matrix.push_back(vec);
        start += chunk;
    }

    for (uint i = 0; i < matrix.size(); i++)
        matrix[i][i] = INF;

    return matrix;
}

template<typename Graph>
Graph GraphParser::Parse(const std::string &filename) {
    std::fstream file;
    file.open(filename, std::ios_base::in);

    if (!file)
        throw std::runtime_error("Could not open the file");

    std::string file_type;
    std::getline(file, file_type);
    Graph rep;


    if (file_type == "NODE_COORD")
    {
        std::vector<Vertex> coordinates = ReadCoordinates(file);
        rep = Graph(coordinates);
    }
    else if (file_type == "MATRIX")
    {
        auto mat = ReadMatrix(file);
        rep = Graph(mat);
    }
    else if (file_type == "FULL_MATRIX")
    {
        auto mat = ReadFullMatrix(file);
        rep = Graph(mat);
    }
    else
        throw std::runtime_error("Invlid file type identifier");

    file.close();
    return rep;
}
