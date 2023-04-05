#ifndef DSA_DRAFT_SPARSENODE_H
#define DSA_DRAFT_SPARSENODE_H


#include <iostream>

class SparseNode {

private:
    int posRow;
    int posCol;
    int posValue;
    SparseNode* next;

    friend class SparseList;

public:
    SparseNode(int p_row, int p_col, int p_val);
    SparseNode(int p_row, int p_col, int p_val, SparseNode* p_next);
    ~SparseNode();
    int getRow();
    int getCol();
    int getValue();
    SparseNode *getNext();
    //copy constructor
    SparseNode(const SparseNode& p_copySrc);
    void output();

};


#endif //DSA_DRAFT_SPARSENODE_H
