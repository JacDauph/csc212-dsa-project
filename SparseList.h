#ifndef DSA_DRAFT_SPARSELIST_H
#define DSA_DRAFT_SPARSELIST_H

#include <vector>
#include <iostream>
#include "SparseNode.h"

class SparseList {
private:
    SparseNode* head;

    void push_front(int data);

    //TODO?
    //make friends of sparsemarix
public:
    //make list with set of vectors (row, collums, value)
    SparseList(std::vector<int> p_rowVec, std::vector<int> p_colVec, std::vector<int> p_valueVec);
    ~SparseList();
    //copy constructor
    SparseList(const SparseList& p_copySrc);
    void push_front(int p_row, int p_col, int p_value);
    std::string toString();
    void output();
    SparseNode * getHead() const;

    SparseList();
};







#endif //DSA_DRAFT_SPARSELIST_H
