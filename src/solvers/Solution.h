#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H

#include <nlohmann/json.hpp>
#include "../graphs/GraphRepresentation.h"
using json = nlohmann::json;
using Tour = std::vector<uint>;
class Solution {
public:
    Solution();
    explicit Solution(uint cost);
    Solution(uint cost, const Tour & path);
    Solution operator = (const Solution & other);
    ~Solution();
    json ToJson();


    uint tour_cost = std::numeric_limits<uint>::max();
    Tour tour;
};


#endif //TSP_SOLUTION_H
