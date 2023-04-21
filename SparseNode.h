#pragma once

class SparseNode {

private:
    int row;
    int col;
    double value;
    SparseNode* next;

    friend class SparseList;

public:
    SparseNode(int p_row, int p_col, double p_val);
    SparseNode(int p_row, int p_col, double p_val, SparseNode* p_next);
    ~SparseNode();

    int getRow();
    int getCol();
    int getValue();
    SparseNode *getNext();

    // Comparison overloads, allows to see if a node is in a position higher or lower than a given node
    bool operator<(SparseNode&);
    bool operator>(SparseNode&);
    bool operator==(SparseNode&);

    // Copy constructor
    SparseNode(SparseNode& p_copySrc);

};
