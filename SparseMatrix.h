#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ostream>
#include "SparseNode.h"

class SparseMatrix {
private:

    SparseNode* head;
    SparseNode* tail;
    int numRows; // Number of rows, used for size
    int numCols; // Number of columns, used for size
    int length = 0;

    void push_back(int,int,double);
    void push_front(int,int,double);
    void remove(int,int);
    void insert(int,int,double);

    bool can_multiply(SparseMatrix& A, SparseMatrix& B);
    bool can_add(SparseMatrix& A, SparseMatrix& B);
    

public:

    SparseMatrix();
    SparseMatrix(int,int);
    SparseMatrix(std::string);
    SparseMatrix(std::vector<std::vector<double>>);
    ~SparseMatrix();

    SparseMatrix(SparseMatrix&);

    SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B);
    SparseMatrix add(SparseMatrix& A, SparseMatrix& B);
    SparseMatrix transpose();

    SparseMatrix operator*(SparseMatrix& p_matrix);
    SparseMatrix operator+(SparseMatrix& p_matrix);
    SparseMatrix operator=(SparseMatrix p_matrix);
    SparseMatrix operator^(int p_power);
    
    void modify(int,int,double);

    void print(std::ostream& os = std::cout);

    int getNumRows();
    int getNumCols();
    int len();
    SparseNode* getHead();
    SparseNode* getTail();
};