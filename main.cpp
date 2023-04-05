#include <iostream>
#include "SparseMatrix.h"

int main() {
    SparseMatrix t1(3);
    t1.output();

    //uses copy constuctor, but own entities
    SparseMatrix t2(t1);
    //t2.insert(1,0,5);
    //t2.insert(2,0,7);
    t2.output();

    SparseMatrix t3;

    //add matrix t1 and add it to t2 and put it in t3
    t3 = t2 * t1;
    t3.output();

    return 0;
}