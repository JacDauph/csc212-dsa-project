#include "SparseMatrix.h"

// Default constructor
SparseMatrix::SparseMatrix(){
    this->numRows = 0;
    this->numCols = 0;
    this->head = nullptr;
    this->tail = nullptr;
}
// Base constructor using on the size and no inputted nodes
SparseMatrix::SparseMatrix(int p_numRows, int p_numCols){
    this->numRows = p_numRows;
    this->numCols = p_numCols;
    this->head = nullptr;
    this->tail = nullptr;
}
// Constructor based on the file. Handles file intake
SparseMatrix::SparseMatrix(std::string fname){

    this->head = nullptr;
    this->tail = nullptr;

    std::fstream file(fname);
    std::string line, test;
    std::stringstream ss;
    double double_value;

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
                std::cout << double_value << std::endl;
                this->push_back(i,j,double_value);
                this->length++;
            }
        }
        ss.clear();
    }
}
// Constructor, takes in a vector of vectors of doubles
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
// Destructor, standard for linked lists
SparseMatrix::~SparseMatrix(){
    delete this->head;
    this->head = nullptr;
}

// Copy constrcutor, copies deeply as to avoid copying the memory addresses
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

//Method that performs the matrix multiplication between 2 sparse matrices and returns a new sparse matrix as an output
SparseMatrix SparseMatrix::multiply(SparseMatrix& A, SparseMatrix& B){
    // Creates a new sparse matrix with the rows of A and the columns of B, as it would happen with normal matricies
    SparseMatrix output = SparseMatrix(A.getNumRows(),B.getNumCols());

    //Transposed to make it easier to apply multiplication operations
    SparseMatrix transpose_B = B.transpose();

    SparseNode* A_node = A.getHead();
    SparseNode* B_node = transpose_B.getHead();

    // A breif check to tell if there are any errors with the entry, although there should be none
    if(!can_multiply(A,B)){std::cout << "Error: Invalid matrix multiplication" << std::endl;return output;}

    // Loops through all nodes in A
    while(A_node != nullptr){
        // Gets the current row we are checking for in multiplication
        int current_row = A_node->getRow();

        B_node = transpose_B.getHead();

        // Loops through all nodes in B
        while(B_node != nullptr){
            // Gets the current col we are checking for in mulitplication
            int current_col = B_node->getRow();

            // Sets temp nodes to loop through to check if multiplied
            SparseNode* temp_A = A_node;
            SparseNode* temp_B = B_node;

            // Sum of the multiplied values
            int sum = 0;

            // Multiplication check for all values applicable
            while(temp_A != nullptr && temp_A->getRow() == current_row && 
                temp_B != nullptr && temp_B->getRow() == current_col){
                
                // Skip A_node
                if(temp_A->getCol() < temp_B->getCol()){

                    temp_A = temp_A->getNext();

                } // Skip B_node
                else if(temp_A->getCol() > temp_B->getCol()){

                    temp_B = temp_B->getNext();

                } // Add the product to the sum if the same location in the matrix
                else{
                    sum += temp_A->getValue() * temp_B->getValue();
                    temp_A = temp_A->getNext();
                    temp_B = temp_B->getNext();
                }

            }
            // Check is viable to add to the output matrix
            if(sum != 0.0){
                output.insert(current_row,current_col,sum);
            }
            // Skip to next viable node for multiplication loop
            while(B_node != nullptr && B_node->getRow() == current_col){
                B_node = B_node->getNext();
            }
        }
        // Skip to next viable node for multiplication loop
        while(A_node != nullptr && A_node->getRow() == current_row){
                A_node = A_node->getNext();
        }
    }
    return output;
}

//Method that performs the addition matrix operation and returns a new sparse matrix as an output
SparseMatrix SparseMatrix::add(SparseMatrix& A, SparseMatrix& B){
    // Sets up a matrix with the same size as both matricies
    SparseMatrix output = SparseMatrix(A.getNumRows(),A.getNumCols());

    // Sets nodes to iterate through
    SparseNode* A_node = A.getHead();
    SparseNode* B_node = B.getHead();

    // Check if able to add, outputs text in case of error
    if(!can_add(A,B)){std::cout << "Error: Invalid matrix addition" << std::endl;return output;}

    // While both nodes are not null
    while(A_node != nullptr || B_node != nullptr){
        // This section checks several cases: 
        // if the node is smaller, push the smaller one first, then progress it to the next
        // if the nodes are in the same location, add their values and then add it to the output, then priogress both nodes
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
// Transposes the current matrix and returns the transposed sparse matrix
SparseMatrix SparseMatrix::transpose(){
    SparseMatrix output = SparseMatrix(this->getNumRows(),this->getNumCols());
    SparseNode* node = this->getHead();

    while(node != nullptr){
        output.insert(node->getCol(),node->getRow(),node->getValue());
        node = node->getNext();
    }

    return output;
}

// Operator overload to allow for multiplication
SparseMatrix SparseMatrix::operator*(SparseMatrix& p_matrix){
    return this->multiply(*this,p_matrix);
}
// Operator overload to allow for addition
SparseMatrix SparseMatrix::operator+(SparseMatrix& p_matrix){
    return this->add(*this,p_matrix);
}
// Operator overload to allow for deep copy assignment to avoid further issues
SparseMatrix SparseMatrix::operator=(SparseMatrix p_matrix){
    if(this != &p_matrix){
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
    return *this;
}
// Operator overload to allow for raising to powers, applicable in implementation in the main
SparseMatrix SparseMatrix::operator^(int p_power){
    SparseMatrix output = SparseMatrix(*this);
    for(int i = 1; i < p_power; i++){
        output = (output * *this);
    }
    return output;
}

// Bools to check if the matricies are able to multiply/add with each other according to their row and column count
bool SparseMatrix::can_multiply(SparseMatrix& A, SparseMatrix& B){
    return A.getNumCols() == B.getNumRows();
}
bool SparseMatrix::can_add(SparseMatrix& A, SparseMatrix& B){
    return (A.getNumCols() == B.getNumCols() && A.getNumRows() == B.getNumRows());
}

//Print method for sparse matrices
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

//Getter Methods
int SparseMatrix::getNumRows(){return this->numRows;}
int SparseMatrix::getNumCols(){return this->numCols;}
int SparseMatrix::len(){return this->length;}
SparseNode* SparseMatrix::getHead(){return this->head;}
SparseNode* SparseMatrix::getTail(){return this->tail;}

// All method below are standard linked list method that are applied to the node type we are using
void SparseMatrix::push_back(int m, int n, double value){
    if(this->head == nullptr){
        this->head = new SparseNode(m,n,value);
        // Assign tail
    }else{
        SparseNode* tmp = this->head;

        while(tmp->next != nullptr){
            tmp = tmp->next;
        }

        tmp->next = new SparseNode(m,n,value);
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