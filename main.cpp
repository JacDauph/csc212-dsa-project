#include <iostream>
#include "SparseMatrix.h"

std::vector<std::vector<double>> file_to_vector(std::string fname){
    std::vector<std::vector<double>> output;
    std::ifstream file(fname);

    std::string line;
    
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::vector<double> row;

        double val;
        while (ss >> val)
        {
            // Add the value to the row
            row.push_back(val);
        }

        // Add the row to the output vector
        output.push_back(row);
    }

    return output;
}

int main(int argc, char*argv[]) {
    std::string fname = argv[1];

    int node, n;

    // Initialize vectors
    std::vector<std::vector<double>> initial_vector,pre_transition_vector;

    pre_transition_vector = file_to_vector(fname);
    
    // Initialize transition matrix 
    SparseMatrix transition = SparseMatrix(pre_transition_vector);
    
    // Do while loop for user input that gets starting node, only accepts integer values
    do{
    std::cout << "Please enter which node to start at: ";
    std::cin >> node;
    }while(isdigit(node));
    
    // Checks if starting node is within range of the transition matrix
    if(node > transition.getNumCols() || node > transition.getNumRows()){
        std::cout << "Starting point is out of range" << "\n"
        "Please enter a integer between " << transition.getNumRows() << " and " << transition.getNumCols() << std::endl;
        
        std::cin >> node;
    }
    
    // Do while loop that gets user input for the amount of iterations, only accepts integer values
    do{
    std::cout << "Please enter the amount of iterations: ";
    std::cin >> n;
    }while(isdigit(n));
    
    // For loop to fill the intiial vector
    initial_vector.push_back({});
    for(int i = 1; i <= transition.getNumRows(); i++){
        if(i != node){
            initial_vector[0].push_back(0);
        }
        else{
            initial_vector[0].push_back(1);
        }
    }
    
    // Turns the initial vector into a sparse matrix
    SparseMatrix initial_matrix = SparseMatrix(initial_vector);
    
    // Calculates the P^n, needed to find X sub n.
    SparseMatrix partial = transition^n;

   
    // Equation where X sub n = intial matrix * P^n
    SparseMatrix state_matrix = (initial_matrix * partial);

    //Output
    state_matrix.print();
}
