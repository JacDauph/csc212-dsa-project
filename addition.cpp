#include "SparseMatrix.h"

int main() {

    SparseMatrix A = SparseMatrix("./Test/test_8.txt");
    SparseMatrix B = SparseMatrix("./Test/test_8.txt");

    //SparseMatrix A = SparseMatrix({{1,2},{3,4}});
    //SparseMatrix B = SparseMatrix({{5,6},{7,8}});

    A.print();
    B.print();

    SparseMatrix added = A + B;

    added.print();
}