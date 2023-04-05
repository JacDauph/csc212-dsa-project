#include "SparseNode.h"

SparseNode::SparseNode(int p_row, int p_col, int p_val) {
    this->posRow = p_row;
    this->posCol = p_col;
    this->posValue = p_val;
    this->next = nullptr;
}

SparseNode::SparseNode(int p_row, int p_col, int p_val, SparseNode* p_next) {
    this->posRow = p_row;
    this->posCol = p_col;
    this->posValue = p_val;
    this->next = p_next;
}

SparseNode::~SparseNode() {
    if(this->next != nullptr){
        delete this->next;
    }
}

void SparseNode::output() {
    std::cout << this->posRow << "\t" << this->posCol << "\t" << this->posValue << "\t" << this->next << "\n";
}

int SparseNode::getRow() {
    return posRow;
}
int SparseNode::getCol() {
    return posCol;
}
int SparseNode::getValue() {
    return posValue;
}

SparseNode *SparseNode::getNext() {
    return next;
}