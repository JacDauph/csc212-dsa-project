#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(int p_n) {
    nRows = p_n;
    nCols = p_n;
    //creates empty list
    //ll = SparseList();
    //creates 3 vectors
    std::vector<int> values;
    std::vector<int> rows;
    std::vector<int> cols;
    // just populates diagonals for testing
    for (int i = 0; i < p_n; i++) {
        rows.push_back(i);
        cols.push_back(i);
        values.push_back(i+1);
    }
    //creates the list using the three filled vectors
    ll = SparseList (rows, cols, values);
    //ll = tmp;
}

//builds with vectors
SparseMatrix::SparseMatrix(int p_rows, int p_cols, std::vector<int> p_rowVec, std::vector<int> p_colVec, std::vector<int> p_valueVec) {
    //rows and cols
    nRows = p_rows;
    nCols = p_cols;
    SparseList tmp(p_rowVec, p_colVec, p_valueVec);
    ll = tmp;
}

//empty matrix
SparseMatrix::SparseMatrix() {
    nRows = 0;
    nCols = 0;
    ll = SparseList();
}

//decon
SparseMatrix::~SparseMatrix() {
}


void SparseMatrix::output() {

    //create zero vector with # of rows and cols
    std::vector<std::vector<int>> full = zeroVector2d(this->nRows, this->nCols);

    SparseNode* temp;
    //first node (start at 0)
    //<0,0,1,1>
    temp = this->ll.getHead();

    //fill 'full' with values, at the locations from getters
    while (temp != nullptr) {
        full[temp->getRow()][temp->getCol()] = temp->getValue();
        temp = temp->getNext();
    }

    //prints values
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            std::cout << full[i][j] << " ";
        }
        std::cout << "\n";
    }

    return;
}

//copy constructor
SparseMatrix::SparseMatrix(const SparseMatrix& p_copySrc) {
    std::cout << "Copying Constructor SparseMatrix\n";

    this->nRows = p_copySrc.nRows;
    this->nCols = p_copySrc.nCols;
    //creates new list (deep copy to prevent two maticies pointing to the same memory)
    this->ll = SparseList(p_copySrc.ll);
}

//plus
SparseMatrix SparseMatrix::operator+(const SparseMatrix &p_add) {
    //creates left 2D vector from caller
    std::vector<std::vector<int>> left = this->toVector2d();
    //right side is passed in by parameter
    std::vector<std::vector<int>> right = p_add.toVector2d();
    //sum vector with all 0s
    std::vector<std::vector<int>> sum = zeroVector2d(this->nCols, this->nCols);

    //adds them together
    for (int i = 0; i < this->nRows; i++) {
        for (int j = 0; j < this->nCols; j++) {
            sum[i][j] = left[i][j] + right[i][j];
        }
    }
    //new matrix created from the sum
    return (SparseMatrix(sum)) ;
}

//multiplier
///*
SparseMatrix SparseMatrix::operator*(const SparseMatrix &p_mult) {
    //creates left 2D vector from caller
    std::vector<std::vector<int>> left = this->toVector2d();
    //right side is passed in by parameter
    std::vector<std::vector<int>> right = p_mult.toVector2d();
    //sum vector with all 0s
    std::vector<std::vector<int>> sum = zeroVector2d(this->nCols, this->nCols);

    //two vectors, left and right
    std::vector<int> leftProduct;
    std::vector<int> rightProduct;

    //adds them together
    for (int i = 0; i < this->nRows; i++) {
        for (int j = 0; j < this->nCols; j++) {
//            leftProduct.push_back(left[i][j]);
//            rightProduct.push_back(right[j][i]);

            sum[i][j] += left[i][j] * right[j][i];

            //sum[i][j] = left[i][j] + right[i][j];

        }
    }



    //new matrix created from the sum
    return (SparseMatrix(sum)) ;
}
//*/

//insert
void SparseMatrix::insert(int p_row, int p_col, int p_val){
    ll.push_front(p_row, p_col, p_val);
}


//being passed in a full 2D matrix
SparseMatrix::SparseMatrix(std::vector<std::vector<int>> p_vector) {
    //gets rows and collumns
    nRows = p_vector.size();
    nCols = p_vector.at(0).size();
    //vectors
    std::vector<int> values;
    std::vector<int> rows;
    std::vector<int> cols;
    // goes through list, when vector isn't a 0,
    // store values in vectors
    for (int i = 0; i < this->nRows; i++) {
        for (int j = 0; j < this->nCols; j++) {
            if (p_vector[i][j] != 0) {
                rows.push_back(i);
                cols.push_back(j);
                values.push_back(p_vector[i][j]);
            }
        }
    }
    //pass made vectors into list constructor
    ll = SparseList (rows, cols, values);
    //ll = temp;
}

//turns Sparse matrix into 2D matrix
std::vector<std::vector<int>> SparseMatrix::toVector2d() const {
    std::vector<std::vector<int>> full = zeroVector2d(this->nRows, this->nCols);

/******************************************************/
    SparseNode* temp;
    temp = this->ll.getHead();

    while (temp != nullptr) {
        full[temp->getRow()][temp->getCol()] = temp->getValue();
        temp = temp->getNext();
    }


    return (full);
}

//creates zero matrix
std::vector<std::vector<int>> SparseMatrix::zeroVector2d(int p_row, int p_col) const {
    std::vector<std::vector<int>> zero;

    //rows (each is a vector)
    for (int i = 0; i < p_row; i++) {
        std::vector<int> temp;
        //cols (another vector)
        for (int j = 0; j < p_col; j++) {
            temp.push_back(0);
        }
        //pushes 0 vector from temp to zero matrix
        zero.push_back(temp);
    }

    return zero;
}





/*
    std::vector<std::vector<int>> left;
    for (int i = 0; i < this->nRows; i++) {
        std::vector<int> temp;
        for (int j = 0; j < this->nCols; j++) {
            temp.push_back(0);
        }
        left.push_back(temp);
    }

    for (int i = 0; i < this->values.size(); i++) {
        left[this->rows.at(i)][this->cols.at(i)] = this->values.at(i);
    }

    */

/*
std::vector<std::vector<int>> right;
for (int i = 0; i < p_add.nRows; i++) {
    std::vector<int> temp;
    for (int j = 0; j < p_add.nCols; j++) {
        temp.push_back(0);
    }
    right.push_back(temp);
}

for (int i = 0; i < p_add.values.size(); i++) {
    right[p_add.rows.at(i)][p_add.cols.at(i)] = p_add.values.at(i);
}
*/



/*    std::vector<std::vector<int>> full;

    for (int i = 0; i < this->nRows; i++) {
        std::vector<int> temp;
        for (int j = 0; j < this->nCols; j++) {
            temp.push_back(0);
        }
        full.push_back(temp);
    }
*/