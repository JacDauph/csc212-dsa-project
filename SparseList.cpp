#include "SparseList.h"

SparseMatrix::SparseMatrix(){
    this->numRows = 0;
    this->numCols = 0;
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
SparseMatrix SparseMatrix::add(SparseMatrix& A, SparseMatrix& B){}

SparseMatrix SparseMatrix::operator*(SparseMatrix& p_matrix){
    return this->multiply(*this,p_matrix);
}
SparseMatrix SparseMatrix::operator+(SparseMatrix& p_matrix){
    return this->add(*this,p_matrix);
}

bool SparseMatrix::can_multiply(SparseMatrix& A, SparseMatrix& B){
    return A.getNumCols() == B.getNumRows();
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