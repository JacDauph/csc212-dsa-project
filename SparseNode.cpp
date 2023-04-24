#include "SparseNode.h"

// Node creation without a next node
SparseNode::SparseNode(int p_row, int p_col, double p_val) {
    this->row = p_row;
    this->col = p_col;
    this->value = p_val;
    this->next = nullptr;
}

// Node creation with a next node
SparseNode::SparseNode(int p_row, int p_col, double p_val, SparseNode* p_next) {
    this->row = p_row;
    this->col = p_col;
    this->value = p_val;
    this->next = p_next;
}

// Copy Constructor
SparseNode::SparseNode(SparseNode& p_copySrc){
    this->row = p_copySrc.getRow();
    this->col = p_copySrc.getCol();
    this->value = p_copySrc.getValue();
    this->next = p_copySrc.getNext();
}

SparseNode::~SparseNode() {
    if(this->next != nullptr){
        delete this->next;
    }
}

//void SparseNode::output() {
//    std::cout << this->row << "\t" << this->col << "\t" << this->value << "\t" << this->next << "\n";
//}

int SparseNode::getRow() {
    return row;
}
int SparseNode::getCol() {
    return col;
}
int SparseNode::getValue() {
    return value;
}

SparseNode *SparseNode::getNext() {
    return next;
}

// Checks to see if the position of the node is more upper-left in the matrix
bool SparseNode::operator<(SparseNode& p_node){
    if(&p_node == nullptr && this != nullptr){return false;}
    if(this == nullptr && &p_node != nullptr){return true;}
    return (this->getRow() < p_node.getRow()) ? true: (this->getRow() > p_node.getRow()) ? false: (this->getCol() < p_node.getCol()) ? true:false;
}

// Checks to see if the position of the node is more lower-right in the matrix
bool SparseNode::operator>(SparseNode& p_node){
    if(&p_node == nullptr && this != nullptr){return true;}
    if(this == nullptr && &p_node != nullptr){return false;}
    return (this->getRow() > p_node.getRow()) ? true: (this->getRow() < p_node.getRow()) ? false: (this->getCol() > p_node.getCol()) ? true:false;
}

// Checks if the position of the node is the same
bool SparseNode::operator==(SparseNode& p_node){
    return !(*this < p_node) && !(*this > p_node);
}