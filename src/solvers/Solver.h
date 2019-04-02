#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "Solution.h"

class Solver {
public:
    Solver();
    virtual ~Solver();
    virtual Solution Solve(const GraphRepresentation &rep) = 0;

};


#endif //TSP_SOLVER_H
