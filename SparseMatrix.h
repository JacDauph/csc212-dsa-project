/*#ifndef DSA_DRAFT_SPARSEMATRIX_H
#define DSA_DRAFT_SPARSEMATRIX_H

#include <vector>
#include <iostream>
#include "SparseList.h"

class SparseMatrix {

private:
    int nRows;
    int nCols;
    //sparse list
    SparseList ll;

    //creates 2D Zero vector
    //based on number of rows and cols
    //3 & 3 -> creates 3x3 matrix with 0s
    std::vector<std::vector<int>> zeroVector2d(int p_row, int p_col) const;


public:
    //creates nxn matrix with diagonals, for testing
    SparseMatrix(int p_n);
    SparseMatrix();
    SparseMatrix(const SparseMatrix& p_copySrc);
    SparseMatrix(const std::vector<std::vector<int>> p_vector);
    //3 vectors
    //read from file to populate 3 vectors, then call this constuctor to create the matrix
    SparseMatrix(int p_rows, int p_cols,std::vector<int> p_rowVec, std::vector<int> p_colVec, std::vector<int> p_valueVec);
    ~SparseMatrix();

    //converts curent sparse matrix into a 2D matrix
    std::vector<std::vector<int>> toVector2d() const;
    void output();

    //addition operator+ overload+
    SparseMatrix operator+(const SparseMatrix& p_add);

    //multipulcation operator
    SparseMatrix operator*(const SparseMatrix& p_mult);

    //insert
    void insert(int p_row, int p_col, int p_val);
};



#endif //DSA_DRAFT_SPARSEMATRIX_H
*/