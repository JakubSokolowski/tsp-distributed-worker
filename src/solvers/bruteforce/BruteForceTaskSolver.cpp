#include "BruteForceTaskSolver.h"
#include <algorithm>
BruteForceTaskSolver::BruteForceTaskSolver(const SymmetricMatrix &graph)
    : graph_m(graph)
{ }

Solution BruteForceTaskSolver::SolveTask(const json &task) {
    std::vector<uint> locked_cities = task["lockedCities"];
    Solution initial = GenerateInitialSolution(locked_cities);
    Solution best_solution = initial;
    auto current_permutation = initial.tour;
    while (std::next_permutation(current_permutation.begin() + locked_cities.size() + 1, current_permutation.end() - 1)) {
        auto current_cost = graph_m.GetTourCost(current_permutation);
        if (current_cost < best_solution.tour_cost) {
            best_solution = Solution(current_cost, current_permutation);
        }
    }
    return best_solution;
}


Solution BruteForceTaskSolver::GenerateInitialSolution(const std::vector<uint> &locked_cities) {
    std::vector<uint> tour(graph_m.GetNumOfVertices());
    std::iota(tour.begin(), tour.end(), 1);
    tour.push_back(tour[0]);

    for(const auto& city: locked_cities){
        tour.erase(std::remove(tour.begin(), tour.end(), city), tour.end());
    }

    auto locked_tour = tour;
    locked_tour.insert(locked_tour.begin() + 1, locked_cities.begin(), locked_cities.end());


    auto cost = graph_m.GetTourCost(locked_tour);
    return Solution(cost, locked_tour);
}
