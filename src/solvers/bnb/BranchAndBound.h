#ifndef TSP_BRANCHANDBOUND_H
#define TSP_BRANCHANDBOUND_H

#include <iostream>
#include <limits>
#include <deque>
#include <stack>
#include <utility>

#include "LittleMatrix.h"
#include "../Solver.h"
#include "../Solution.h"


using std::stack;
using std::deque;
using std::pair;
using std::cout;
using std::endl;

struct Node {
    int parent_key = -1;
    uint lower_bound;
    Edge path;
    bool included = false;
};



class BranchAndBound: public Solver {
public:

    explicit BranchAndBound(LittleMatrix &m);
    BranchAndBound();
    void AssignMatrix(const LittleMatrix &m);
    void AddIndices(LittleMatrix &m);

    Solution Solve(const GraphRepresentation& representation);
    uint FindBranchingPositionAndRegret(const LittleMatrix &m, Edge &path, Position &pos);

    void RemoveSubtour(LittleMatrix &m, int index, Edge &path);
    uint VisitedNodesCount() { return (uint)tree_m.size(); }
    Tour RetrieveNewTourFromTree(int index, uint begin);
    void UpdateCurrentBestSolution(LittleMatrix &m);


    void FindTour();

    Tour GetLastTour() { return current_best_tour_m; }
    uint GetLastCost() { return current_smallest_cost_m; }
    bool IsOptimal() { return optimal; }


private:
    uint infinity;
    LittleMatrix initial_matrix_m;
    uint current_smallest_cost_m = std::numeric_limits<uint>::max();
    deque<Node> tree_m;
    Tour current_best_tour_m;
    bool optimal = 0;

};


#endif //TSP_BRANCHANDBOUND_H
