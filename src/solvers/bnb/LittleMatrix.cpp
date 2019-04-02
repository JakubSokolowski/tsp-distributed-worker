#include "LittleMatrix.h"

LittleMatrix::LittleMatrix(uint rows_num, uint cols_num)
    : data_m(Matrix(rows_num, std::vector<uint>(cols_num, INF)))
    , rows_num_m(rows_num)
    , columns_num_m(cols_num)
{ }

LittleMatrix::LittleMatrix(const Matrix &matrix)
        : data_m(matrix)
        , rows_num_m(static_cast<uint>(matrix.size()))
        , columns_num_m(static_cast<uint>(matrix.size()))
{ }

LittleMatrix::LittleMatrix(const GraphRepresentation &graph) {
    rows_num_m = columns_num_m = graph.GetNumOfVertices();
    data_m = Matrix(rows_num_m, vector<uint >(columns_num_m, INF));
    for (uint i = 0; i < rows_num_m; i++)
        for (uint j = 0; j < columns_num_m; j++)
            SetCost(i, j, graph.GetWeight(i, j));
}

void LittleMatrix::AssingIndices() {
    AddRow(0);
    AddColumn(0);
    for(uint i = 0; i < rows_num_m; i++) {
        SetCost(0, i, i);
        SetCost(i, 0 ,i);
    }

}

uint LittleMatrix::FindRowMinimum(uint row) const {
    auto min = INF;
    for (uint column = 1; column < columns_num_m; column++) {
        auto current_cost = GetCost(row, column);
        if (current_cost != INF && current_cost < min)
            min = current_cost;
    }
    return min;
}

uint LittleMatrix::FindRowMinimum(uint row, uint disabled_column) const {
    auto min = INF;
    for (uint column = 1; column < columns_num_m; column++) {
        auto current_cost = GetCost(row, column);
        if (current_cost != INF && current_cost < min && column != disabled_column)
            min = current_cost;
    }
    return min;

}

uint LittleMatrix::FindColumnMinimum(uint column) const {
    auto min = INF;
    for (uint row = 1; row < rows_num_m; row++) {
        auto current_cost = GetCost(row, column);
        if (current_cost != INF && current_cost < min)
            min = current_cost;
    }
    return min;
}

uint LittleMatrix::FindColumnMinimum(uint column, uint disabled_row) const {
    auto min = INF;
    for (uint row = 1; row < rows_num_m; row++) {
        auto current_cost = GetCost(row, column);
        if (current_cost != INF && current_cost < min && row != disabled_row)
            min = current_cost;
    }
    return min;
}

uint LittleMatrix::FindHighestPenaltyEdge(Edge &edge, Position &position) const {
    uint size = rows_num_m;
    uint max = 0;

    for (uint i = 1; i < size; i++) {
        for (uint j = 1; j < size; j++) {
            if (GetCost(i, j) == 0) {
                auto val = FindRowMinimum(i, j) + FindColumnMinimum(j, i);
                if (max < val || max < 0) {
                    max = val;

                    position.first = i;
                    position.second = j;

                    edge.first = GetCost(i, 0);
                    edge.second = GetCost(j, 0);
                }
            }
        }
    }
    return max;

}

uint LittleMatrix::ReduceRow(uint row) {
    auto min = FindRowMinimum(row);
    for (uint column = 1; column < columns_num_m; column++)
    {
        auto lower_bound = GetCost(row, column);
        if (lower_bound != INF)
            SetCost(row, column, lower_bound - min);
    }
    return min;
}

uint LittleMatrix::ReduceAllRows() {
    uint sum_of_row_minima = 0;
    for (uint row = 1; row < rows_num_m; row++)
        sum_of_row_minima += ReduceRow(row);
    return sum_of_row_minima;
}

uint LittleMatrix::ReduceColumn(uint column) {
    auto min = FindColumnMinimum(column);
    for (uint row = 1; row < rows_num_m; row++)
    {
        auto lower_bound = GetCost(row, column);
        if (lower_bound != INF)
            SetCost(row, column, lower_bound - min);
    }
    return min;

}

uint LittleMatrix::ReduceAllColumns() {
    uint sum_of_column_minima = 0;
    for (uint column = 1; column < columns_num_m; column++)
        sum_of_column_minima += ReduceColumn(column);
    return sum_of_column_minima;
}

// Reduced the matrix subtracting all the i and j minima from
// their corresponding rows and columns, then returns
// the sum of this minima - the lower bound
uint LittleMatrix::ReduceMatrix() {
    return ReduceAllRows() + ReduceAllColumns();
}

void LittleMatrix::AddRow(uint row_index) {
    auto it = data_m.begin() + row_index;
    data_m.insert(it, vector<uint >(columns_num_m, INF));
    ++rows_num_m;
}

void LittleMatrix::RemoveRow(uint row_index) {
    auto it = data_m.begin() + row_index;
    data_m.erase(it);
    --rows_num_m;
}

void LittleMatrix::AddColumn(uint column_index) {
    for (uint row = 0; row < rows_num_m; row++) {
        auto it = data_m[row].begin() + column_index;
        data_m[row].insert(it, INF);
    }
    ++columns_num_m;
}

void LittleMatrix::RemoveColumn(uint column_index) {
    for (uint row = 0; row < rows_num_m; row++) {
        auto it = data_m[row].begin() + column_index;
        data_m[row].erase(it);
    }
    --columns_num_m;
}


uint LittleMatrix::GetCost(uint row_index, uint column_index) const {
    return data_m[row_index][column_index];
}

void LittleMatrix::SetCost(uint row_index, uint column_index, uint value) {
    data_m[row_index][column_index] = value;
}

uint LittleMatrix::operator()(uint row, uint column) {
    return GetCost(row, column);
}

LittleMatrix::LittleMatrix(const LittleMatrix &other)
        : data_m(other.data_m)
        , rows_num_m(other.rows_num_m)
        , columns_num_m(other.columns_num_m)
{ }

LittleMatrix::~LittleMatrix() = default;
