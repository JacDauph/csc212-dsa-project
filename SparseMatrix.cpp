#include "SparseMatrix.h"

#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

SparseMatrix::SparseMatrix(){
    this->numRows = 0;
    this->numCols = 0;
    this->head = nullptr;
    this->tail = nullptr;
}
SparseMatrix::SparseMatrix(int p_numRows, int p_numCols){
    this->numRows = p_numRows;
    this->numCols = p_numCols;
    this->head = nullptr;
    this->tail = nullptr;
}
SparseMatrix::SparseMatrix(std::string fname){
    std::fstream file(fname);
    std::string line;
    std::stringstream ss;
    double double_value;

    getline(file,line);

    ss << line;
    ss >> this->numRows >> this->numCols;

    int i = 0, j = 0;
    while(getline(file,line)){
        ss << line;
        while(ss >> double_value){
            if(double_value != 0.0){
                this->push_back(i,j,double_value);
            }
            j++;
        }
        i++;
        j = 0;
    }
}
SparseMatrix::SparseMatrix(std::vector<std::vector<double>> p_vector){
    this->numRows = p_vector.size();
    this->numCols = p_vector[0].size();
    this->head = nullptr;
    this->tail = nullptr;
}
SparseMatrix::~SparseMatrix(){
    delete this->head;
    this->head = nullptr;
}

SparseMatrix::SparseMatrix(SparseMatrix& p_matrix){
    this->numRows = p_matrix.getNumRows();
    this->numCols = p_matrix.getNumCols();
    this->head = nullptr;
    this->tail = nullptr;

    SparseNode* temp = p_matrix.head;
    while(temp != nullptr){
        this->push_back(temp->getRow(), temp->getCol(), temp->getValue());
        temp = temp->next;
    }
}

SparseMatrix SparseMatrix::multiply(SparseMatrix& A, SparseMatrix& B){}
SparseMatrix SparseMatrix::add(SparseMatrix& A, SparseMatrix& B){
    SparseMatrix output = SparseMatrix(A.getNumRows(),A.getNumCols());

    SparseNode* A_node = A.getHead();
    SparseNode* B_node = B.getHead();

    while(A_node != nullptr || B_node != nullptr){
        if(A_node > B_node){
            output.push_back(A_node->getRow(),A_node->getCol(),A_node->getValue());
            A_node = A_node->getNext();
        }else if(A_node < B_node){
            output.push_back(B_node->getRow(),B_node->getCol(),B_node->getValue());
            B_node = B_node->getNext();
        }else{
            output.push_back(A_node->getRow(),A_node->getCol(),A_node->getValue() + B_node->getValue());
            A_node = A_node->getNext();
            B_node = B_node->getNext();
        }
    }

    return output;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix& p_matrix){
    return this->multiply(*this,p_matrix);
}
SparseMatrix SparseMatrix::operator+(SparseMatrix& p_matrix){
    return this->add(*this,p_matrix);
}

bool SparseMatrix::can_multiply(SparseMatrix& A, SparseMatrix& B){
    return A.getNumCols() == B.getNumRows();
}
bool SparseMatrix::can_add(SparseMatrix& A, SparseMatrix& B){
    return (A.getNumCols() == B.getNumCols() && A.getNumRows() == B.getNumRows());
}

void SparseMatrix::print(std::ostream& os){
    os << std::fixed << std::setprecision(2);
    SparseNode* temp = this->head;
    for(int i = 0; i < this->getNumRows(); i++){
        for(int j = 0; j < this->getNumCols(); j++){
            if(temp != nullptr){
                if(i == temp->getRow() && j == temp->getCol()){
                    os << temp->getValue() << " ";
                    temp = temp->next;
                }else{os << 0.00 << " ";}
            }
        }
        os << std::endl;
    }
}

int SparseMatrix::getNumRows(){return this->numRows;}
int SparseMatrix::getNumCols(){return this->numCols;}

void SparseMatrix::push_back(int m, int n, double value){ // Specifically for ease of copying sparse matricies
    if(this->head == nullptr){
        this->head = new SparseNode(m,n,value);
        this->tail = this->head;
    }else{
        SparseNode* temp = this->head;

        while(temp->next != nullptr){
            temp = temp->next;
        }

        temp->next = new SparseNode(m,n,value);
    }
}
void SparseMatrix::push_front(int m, int n, double value){
    if(this->head == nullptr){
        this->head = new SparseNode(m,n,value);
        this->tail = this->head;
    }else{
        SparseNode* temp = new SparseNode(m,n,value, this->head);
        this->head = temp;
    }
}
void SparseMatrix::remove(int m, int n){
    SparseNode* temp = this->head;
    SparseNode* previous = nullptr;
    SparseNode test = SparseNode(m,n,0);

    // Search for the element
    while(temp != nullptr && !(*temp == test)){
        previous = temp;
        temp = temp->next;
    }

    if(temp != nullptr){
        // Special case: deleting the head
        if(temp == this->head){
            this->head = temp->next;
        }else{
            previous->next = temp->next;
        }

        temp->next = nullptr;
        delete temp;
    }
}
/*
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
    //std::cout << "Copy Constructor SparseList\n";
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
*/