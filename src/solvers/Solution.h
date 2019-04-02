#ifndef TSP_SOLUTION_H
#define TSP_SOLUTION_H

#include "../graphs/GraphRepresentation.h"

using Tour = std::vector<uint>;
class Solution {
public:
    Solution();
    explicit Solution(uint cost);
    Solution(uint cost, const Tour & path);
    Solution operator = (Solution & other);
    ~Solution();

    uint tour_cost = std::numeric_limits<uint>::max();
    Tour tour;
};


#endif //TSP_SOLUTION_H
