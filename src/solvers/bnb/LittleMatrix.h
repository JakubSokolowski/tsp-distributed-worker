#ifndef TSP_LITTLEMATRIX_H
#define TSP_LITTLEMATRIX_H

#include "../../graphs/GraphRepresentation.h"

using std::vector;

using Edge = std::pair<uint, uint>;
using Position = std::pair<uint, uint>;


class LittleMatrix {
public:
    explicit LittleMatrix(uint nbRows = 0, uint nbColumns = 0);
    explicit LittleMatrix(const Matrix &matrix);
    explicit LittleMatrix(const GraphRepresentation &graph);
    LittleMatrix(const LittleMatrix &other);
    void AssingIndices();

    uint GetEmptyValue() const { return INF; }

    uint FindRowMinimum(uint row) const;
    uint FindRowMinimum(uint row, uint disabled_column) const;
    uint FindColumnMinimum(uint column) const;
    uint FindColumnMinimum(uint column, uint disabled_row) const;

    uint ReduceRow(uint row);
    uint ReduceColumn(uint column);
    uint ReduceAllRows();
    uint ReduceAllColumns();
    uint ReduceMatrix();

    uint FindHighestPenaltyEdge(Edge &edge, Position &position) const;

    void AddRow(uint row_index);
    void RemoveRow(uint row_index);

    void AddColumn(uint column_index);
    void RemoveColumn(uint column_index);

    uint GetRowNum() const { return rows_num_m; }
    uint GetColumnCount() const  { return columns_num_m; }

    uint GetCost(uint row_index, uint column_index) const;
    void SetCost(uint row_index, uint column_index, uint value);

    uint operator() (uint row, uint column);

    ~LittleMatrix();

private:

    uint rows_num_m;
    uint columns_num_m;
    Matrix data_m;
};


#endif //TSP_LITTLEMATRIX_H
