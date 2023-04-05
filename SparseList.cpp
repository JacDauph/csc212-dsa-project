#include "SparseList.h"

//constructor
SparseList::SparseList(std::vector<int> p_rowVec, std::vector<int> p_colVec, std::vector<int> p_valueVec) {
    this->head = nullptr;
    for (int i = 0; i < p_rowVec.size(); i++) {
        push_front(p_rowVec.at(i), p_colVec.at(i), p_valueVec.at(i));
    }
};

void SparseList::push_front(int p_row, int p_col, int p_value) {
    SparseNode *newNode = new SparseNode(p_row, p_col, p_value, this->head);
    this->head = newNode;
}

SparseList::~SparseList() {
    head = nullptr;
}

//Copy Constructor
SparseList::SparseList(const SparseList& p_copySrc) {
    std::cout << "Copy Constructor SparseList\n";
    this->head = nullptr;
    SparseNode * last = nullptr;
    SparseNode* tmp = p_copySrc.getHead();
    while(tmp != nullptr){
        this->head = new SparseNode(tmp->getRow(), tmp->getCol(), tmp->getValue(), this->head);
        tmp = tmp->getNext();
    }

}


std::string SparseList::toString() {
    std::string stringified;
    SparseNode* tmp = this->head;
    while(tmp != nullptr){
        stringified += "[" + std::to_string(tmp->posRow) + "][";
        stringified += std::to_string(tmp->posCol) + "]:";
        stringified += std::to_string(tmp->posValue) + " ";
        tmp = tmp->next;
    }
    return stringified;
}

void SparseList::output() {
    std::string stringified;
    SparseNode* tmp = this->head;
    while(tmp != nullptr){
        stringified += "[" + std::to_string(tmp->posRow) + "][";
        stringified += std::to_string(tmp->posCol) + "]:";
        stringified += std::to_string(tmp->posValue) + "/n";
        std::cout << stringified;
        stringified = "";
        tmp = tmp->next;
    }
}

SparseNode * SparseList::getHead() const {
    return this->head;
}

SparseList::SparseList() {

}