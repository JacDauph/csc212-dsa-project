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

    this->head = nullptr;
    this->tail = nullptr;

    std::fstream file(fname);
    std::string line;
    std::stringstream ss;
    double double_value;
    int test;

    getline(file,line);
    ss << line;
    ss >> this->numRows >> this->numCols;
    ss.clear();

    for(int i = 0; i < this->getNumRows(); i++){
        getline(file,line);
        ss << line;
        for(int j = 0; j < this->getNumCols(); j++){
            ss >> double_value;
            if(double_value != 0.0){
                this->push_back(i,j,double_value);
                this->length++;
            }
        }
        ss.clear();
    }
}
SparseMatrix::SparseMatrix(std::vector<std::vector<double>> p_vector){
    this->numRows = p_vector.size();
    this->numCols = p_vector[0].size();
    this->head = nullptr;
    this->tail = nullptr;

    for (int i = 0; i < this->getNumRows(); i++){
        for (int j = 0; j < this->getNumCols(); j++){
            if(p_vector[i][j] != 0.0){
                this->push_back(i,j,p_vector[i][j]);
                this->length++;
            }
        }
    }

}
SparseMatrix::~SparseMatrix(){
    delete this->head;
    this->head = nullptr;
}

SparseMatrix::SparseMatrix(SparseMatrix& p_matrix){
    this->numRows = p_matrix.getNumRows();
    this->numCols = p_matrix.getNumCols();
    this->length = p_matrix.len();
    this->head = nullptr;
    this->tail = nullptr;

    SparseNode* temp = p_matrix.head;
    while(temp != nullptr){
        this->push_back(temp->getRow(), temp->getCol(), temp->getValue());
        temp = temp->next;
    }
}

SparseMatrix SparseMatrix::multiply(SparseMatrix& A, SparseMatrix& B){
    SparseMatrix output = SparseMatrix(A.getNumCols(),B.getNumRows());

    SparseMatrix transpose_B = B.transpose();

    SparseNode* A_node = A.getHead();
    SparseNode* B_node = transpose_B.getHead();

    if(!can_multiply(A,B)){std::cout << "Error: Invalid matrix multiplication" << std::endl;return output;}

    while(A_node != nullptr){
        int current_row = A_node->getRow();

        B_node = transpose_B.getHead();

        while(B_node != nullptr){
            int current_col = B_node->getRow();

            SparseNode* temp_A = A_node;
            SparseNode* temp_B = B_node;

            int sum = 0;

            while(temp_A != nullptr && temp_A->getRow() == current_row && 
                temp_B != nullptr && temp_B->getRow() == current_col){
                
                if(temp_A->getCol() < temp_B->getCol()){

                    temp_A = temp_A->getNext();

                }else if(temp_A->getCol() > temp_B->getCol()){

                    temp_B = temp_B->getNext();

                }else{
                    sum += temp_A->getValue() * temp_B->getValue();
                    temp_A = temp_A->getNext();
                    temp_B = temp_B->getNext();
                }

            }
            if(sum != 0.0){
                output.insert(current_row,current_col,sum);
            }
            while(B_node != nullptr && B_node->getRow() == current_col){
                B_node = B_node->getNext();
            }
        }
        while(A_node != nullptr && A_node->getRow() == current_row){
                A_node = A_node->getNext();
        }
    }
    return output;
}
SparseMatrix SparseMatrix::add(SparseMatrix& A, SparseMatrix& B){
    SparseMatrix output = SparseMatrix(A.getNumRows(),A.getNumCols());

    SparseNode* A_node = A.getHead();
    SparseNode* B_node = B.getHead();

    if(!can_add(A,B)){std::cout << "Error: Invalid matrix addition" << std::endl;return output;}

    while(A_node != nullptr || B_node != nullptr){
        //std::cout << A_node << std::endl;
        //std::cout << B_node << std::endl << std::endl;
        if(*A_node < *B_node){
            output.push_back(A_node->getRow(),A_node->getCol(),A_node->getValue());
            A_node = A_node->getNext();
        }else if(*A_node > *B_node){
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
SparseMatrix SparseMatrix::transpose(){
    SparseMatrix output = SparseMatrix(this->getNumRows(),this->getNumCols());
    SparseNode* node = this->getHead();

    while(node != nullptr){
        output.insert(node->getCol(),node->getRow(),node->getValue());
        node = node->getNext();
    }

    return output;
}

SparseMatrix SparseMatrix::operator*(SparseMatrix& p_matrix){
    return this->multiply(*this,p_matrix);
}
SparseMatrix SparseMatrix::operator+(SparseMatrix& p_matrix){
    return this->add(*this,p_matrix);
}
SparseMatrix SparseMatrix::operator=(SparseMatrix p_matrix){
    if(this != &p_matrix){
        this->numRows = p_matrix.getNumRows();
        this->numCols = p_matrix.getNumCols();
        this->length = p_matrix.len();
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;

        SparseNode* temp = p_matrix.head;
        while(temp != nullptr){
            this->push_back(temp->getRow(), temp->getCol(), temp->getValue());
            temp = temp->next;
        }
    }
    return *this;
}
SparseMatrix SparseMatrix::operator^(int p_power){
    SparseMatrix output = SparseMatrix(*this);
    output.print();
    std::cout << output.getHead() << std::endl;
    std::cout << (*this).getHead() << std::endl;
    for(int i = 1; i < p_power; i++){
        output = (output * *this);
    }
    return output;
}

bool SparseMatrix::can_multiply(SparseMatrix& A, SparseMatrix& B){
    return A.getNumCols() == B.getNumRows();
}
bool SparseMatrix::can_add(SparseMatrix& A, SparseMatrix& B){
    return (A.getNumCols() == B.getNumCols() && A.getNumRows() == B.getNumRows());
}

void SparseMatrix::print(std::ostream& os){
    os << std::setprecision(2);
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
int SparseMatrix::len(){return this->length;}
SparseNode* SparseMatrix::getHead(){return this->head;}
SparseNode* SparseMatrix::getTail(){return this->tail;}

void SparseMatrix::push_back(int m, int n, double value){
    if(this->head == nullptr){
        this->head = new SparseNode(m,n,value);
        this->tail = this->head;
    }else{
        this->tail->next = new SparseNode(m,n,value,this->tail->next);
        this->tail = this->tail->next;
    }
    this->length++;
}
void SparseMatrix::push_front(int m, int n, double value){
    if(this->head == nullptr){
        this->head = new SparseNode(m,n,value);
        this->tail = this->head;
    }else{
        SparseNode* temp = new SparseNode(m,n,value, this->head);
        this->head = temp;
    }
    this->length++;
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
    this->length--;
}
void SparseMatrix::insert(int m, int n, double value){
    SparseNode test_node = SparseNode(m,n,0);
    
    if(!this->head){    // this->head == nullptr
        this->head = new SparseNode(m,n,value);
        this->tail = this->head;
    }else if(test_node < *(this->head)){
        this->push_front(m,n,value);
        return;
    }else if(*(this->tail) < test_node){
        this->push_back(m,n,value);
        return;
    }else{
        SparseNode* tmp = this->head;

        while(*(tmp->next) < test_node){
            tmp = tmp->next;
        }
        SparseNode* tmp2 = new SparseNode(m,n,value,tmp->next);
        //tmp2->next = tmp->next;
        tmp->next = tmp2;
        this->length++;
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