#include "Solution.h"

Solution::Solution() = default;

Solution::Solution(uint cost)
        : tour_cost(cost)
{ }

Solution::Solution(uint cost, const Tour &t)
        : tour_cost(cost)
        , tour(t)
{ }

Solution Solution::operator=(Solution &other) {
    tour_cost = other.tour_cost;
    tour = other.tour;
    return *this;
}

Solution::~Solution() = default;
