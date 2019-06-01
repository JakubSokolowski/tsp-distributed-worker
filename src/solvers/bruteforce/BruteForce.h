#ifndef TSP_WORKER_BRUTEFORCE_H
#define TSP_WORKER_BRUTEFORCE_H


#include "../Solver.h"

class BruteForce : public Solver {
public:
    Solution Solve(GraphRepresentation &representation);
};


#endif //TSP_WORKER_BRUTEFORCE_H
