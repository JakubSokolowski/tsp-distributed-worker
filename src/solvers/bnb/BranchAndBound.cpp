#include "BranchAndBound.h"

BranchAndBound::BranchAndBound() = default;

BranchAndBound::BranchAndBound(LittleMatrix &m) {
    AssignMatrix(m);
}

void BranchAndBound::AssignMatrix(const LittleMatrix &m) {
    initial_matrix_m = m;
    AddIndices(initial_matrix_m);
}

void BranchAndBound::AddIndices(LittleMatrix &m) {
    m.AddRow(0);
    m.AddColumn(0);
    uint row_count = m.GetRowNum();
    for(uint i= 0; i < row_count; i++) {
        m.SetCost(0, i, i);
        m.SetCost(i, 0, i);
    }
}

Solution BranchAndBound::Solve(const GraphRepresentation &representation) {
    auto matrix = LittleMatrix(representation);
    AssignMatrix(matrix);
    FindTour();
    current_best_tour_m.push_back(1);
    return Solution(current_smallest_cost_m, current_best_tour_m);
}

uint BranchAndBound::FindBranchingPositionAndRegret(const LittleMatrix &m, Edge &path, Position &pos) {
    uint size = m.GetRowNum();
    int max = -1;
    for (uint i = 1; i < size; i++) {
        for (uint j = 1; j < size; j++) {
            // Find where there was minimum
            if (m.GetCost(i, j) == 0) {
                // Find the max Cost of all the minima in matrix
                // Disable rows and column
                auto val = m.FindRowMinimum(i, j) + m.FindColumnMinimum(j, i);
                if (max < (uint)val || max < 0) {
                    max = val;
                    // Remember position in current matrix
                    pos.first = i;
                    pos.second = j;

                    /*
                    The position is not necessarily in matrix is not equal to the edge

                    NORMAL									DISABLED

                    0 1 2 3 4	Disable i and col (2,3) ->   0 1 2 4
                    0  - 2 8 9 3 								0  - 2 8 3
                    1  4 - 5 6 3 <- the (1,3) pos is 6			1  4 - 5 3  <- now the (1,3) position in matrix is 5
                    2  1 3 - 6 2	the edge (1,2) is 6			3  3 4 5 7	   but the edge coresponding to that pos
                    3  3 4 5 - 7								4  2 9 2 -	   is not (1,3) but (1,2)
                    4  2 9 2 3 -

                    The easiest way of tracking edges is to extend the matrix by one i and j
                    and keep the indices in there. That way, when reducing the matrix, we can still
                    keep track of the edges. The 0 i and 0 j are not taken into account
                    when searching for i and col minima and reducing the matrix
                    */

                    // The actual index of edge i position is stored in in first i, same for j
                    path.first = m.GetCost(i, 0);
                    path.second = m.GetCost(0, j);
                }
            }
        }
    }
    return static_cast<uint>(max);
}

void BranchAndBound::RemoveSubtour(LittleMatrix &m, int index, Edge &path) {
    uint size = m.GetColumnCount();
    Position pos;
    int found_segment_num = 0;
    vector<pair<uint, uint>> paths;

    // Research of all the included path
    while (index)
    { // Iterate until we are not arrived at the root
        if (!tree_m[index].included)
            paths.push_back(tree_m[index].path);
        index = tree_m[index].parent_key;
    }

    // Research of the longest subtour
    deque<uint> subtour = { path.first, path.second };
    bool found = true;
    while (found) {
        found = false;
        for (const auto &segment : paths) {
            // Check that "segment" go ahead in a subtour
            if (segment.second == subtour.front()) {
                subtour.push_front(segment.second);
                subtour.push_front(segment.first);
                found = true;
                break;
            }
                // Check that "segment" go behind in a subtour
            else if (segment.first == subtour.back()) {
                subtour.push_back(segment.first);
                subtour.push_back(segment.second);
                found = true;
                break;
            }
        }
    }

    // Research of the segment to delete in the matrix
    for (uint i = 1; i < size; i++) {
        if (m.GetCost(i, 0) == subtour.back()) {
            pos.first = i;
            found_segment_num++;
        }
        if (m.GetCost(0, i) == subtour.front()) {
            pos.second = i;
            found_segment_num++;
        }
    }

    // If the segment to delete has been found, then delete it by giving him an infinite cost
    if (found_segment_num == 2)
        m.SetCost(pos.first, pos.second, INF);
}

Tour BranchAndBound::RetrieveNewTourFromTree(int index, uint begin) {
    vector<Edge> path;
    Tour tour;

    // Retrieval of the path stored in a branch's tree
    while (index) {
        // Iterate until we are not arrived at the root
        if (!tree_m[index].included)            // If it is a node without regret cost
            path.push_back(tree_m[index].path); // then we add this segment to the path
        index = tree_m[index].parent_key;
    }

    // Search for the edge that contains beginning
    uint path_size = (uint)path.size();
    for (uint i = 0; i < path.size(); i++) {
        if (path[i].first == begin) {
            tour.push_back(path[i].first);
            tour.push_back(path[i].second);
            path.erase(path.begin() + i);
        }
    }

    //  Order the rest of the tour
    while (tour.size() != path_size){
        for (uint i = 0; i < path.size(); i++) {
            if (tour.back() == path[i].first) {
                tour.push_back(path[i].second);
                path.erase(path.begin() + i);
            }
        }
    }

    return tour;
}

void BranchAndBound::UpdateCurrentBestSolution(LittleMatrix &m) {
    Node node;

    for (uint i = 1; i < 3; i++) {
        for (uint j = 1; j < 3; j++) {
            if (m.GetCost(i, j) == 0) {
                node.path.first = m.GetCost(i, 0);
                node.path.second = m.GetCost(0, j);
                node.lower_bound = tree_m.back().lower_bound;
                node.parent_key = static_cast<int>(tree_m.size() - 1);
                tree_m.push_back(node);
            }
        }
    }
}

void BranchAndBound::FindTour() {
    // Subset with highest penalty, branching to the right
    // This is the node where the rows and columns will be crossed out
    Node right_node;
    Node left_node;
    left_node.included = true;

    Position pos;
    stack<pair<int, LittleMatrix>> matrices;
    // Matrix associated to node
    pair<int, LittleMatrix> matrix;

    // Push initial matrix on stack
    matrix.first = 0;
    matrix.second = initial_matrix_m;

    matrices.push(matrix);

    while (!matrices.empty())
    {
        int id = matrices.top().first;
        LittleMatrix m = matrices.top().second;
        matrices.pop();

        // Find the lower bound of matrix, by reducing it
        right_node.lower_bound = m.ReduceMatrix();
        if (id == 0)
            tree_m.push_back(right_node);

        // If matrix is 3x3 time to trace back the path - 2x2 costs and 1 row and column of indices
        while (m.GetRowNum() > 3 && tree_m[id].lower_bound < current_smallest_cost_m) {
            // Calculate new lower bound for left node
            left_node.lower_bound = tree_m[id].lower_bound + FindBranchingPositionAndRegret(m, right_node.path, pos);
            left_node.parent_key = id;
            tree_m.push_back(left_node);

            // Branching to the left
            if (left_node.lower_bound < current_smallest_cost_m) {
                matrix.first = (int)tree_m.size() - 1;
                matrix.second = m;
                matrix.second.SetCost(pos.first, pos.second, infinity);
                matrices.push(matrix);
            }

            // Branching to the right

            // Remove rows, columns, and subtours
            m.RemoveRow(pos.first);
            m.RemoveColumn(pos.second);
            RemoveSubtour(m, (int)tree_m.size() - 1, right_node.path);

            // Calculate new lower bound - parent lower bound + sum of reduction
            right_node.lower_bound = tree_m[id].lower_bound + m.ReduceMatrix();
            right_node.parent_key = id;
            tree_m.push_back(right_node);

            id = (int)tree_m.size() - 1;
        }

        // Update the best tour and the current_smallest_cost_m value
        if (m.GetRowNum() == 3)
        {
            if (right_node.lower_bound < current_smallest_cost_m)
            {
                UpdateCurrentBestSolution(m);
                current_smallest_cost_m = right_node.lower_bound;
                current_best_tour_m = RetrieveNewTourFromTree((int) tree_m.size() - 1, 1);
            }
        }
    }
    optimal = true;
}
