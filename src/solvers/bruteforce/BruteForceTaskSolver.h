#ifndef TSP_WORKER_BRUTEFORCETASKSOLVER_H
#define TSP_WORKER_BRUTEFORCETASKSOLVER_H

#include  <nlohmann/json.hpp>
#include "../../graphs/GraphRepresentation.h"
#include "../Solution.h"
#include "../../graphs/SymmetricMatrix.h"

using json = nlohmann::json;

class BruteForceTaskSolver {
public:
    BruteForceTaskSolver(const SymmetricMatrix& graph);
    Solution SolveTask(const json & task);
    void UpdateGraph(const SymmetricMatrix& graph) {
        graph_m = graph;
    }
private:
    Solution GenerateInitialSolution(const std::vector<uint>& locked_cities);
    SymmetricMatrix graph_m;
};


#endif //TSP_WORKER_BRUTEFORCETASKSOLVER_H
