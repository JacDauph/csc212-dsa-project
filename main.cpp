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

    int node, n; //this might need to be a double? n is for the initial state matrix * P^n

    std::vector<std::vector<double>> initial_vector,pre_transition_vector;

    pre_transition_vector = file_to_vector(fname);
    SparseMatrix transition = SparseMatrix(pre_transition_vector);
    transition.print();

    do{
    std::cout << "Please enter which node to start at: ";
    std::cin >> node;
    //std::cout << !(isdigit(node)) << std::endl;
    }while(isdigit(node));

    if(node > transition.getNumCols() || node > transition.getNumRows()){
        std::cout << "Starting point is out of range" << "\n"
        "Please enter a integer between " << transition.getNumRows() << " and " << transition.getNumCols() << std::endl;
        
        std::cin >> node;
    }
    

    do{
    std::cout << "Please enter the amount of iterations: ";
    std::cin >> n;
    }while(isdigit(n));

    initial_vector.push_back({});
    for(int i = 1; i <= transition.getNumRows(); i++){
        if(i != node){
            initial_vector[0].push_back(0);
        }
        else{
            initial_vector[0].push_back(1);
        }
    }

    //Possible one liner for for loop above
    // for(int i = 0; i <= transition.getNumRows(); i++) initial_vector[0].push_back(i == node ? 1 : 0);

    SparseMatrix initial_matrix = SparseMatrix(initial_vector);

    SparseMatrix partial = transition * transition;
    partial.print();

    std::cout << transition.getHead() << std::endl;
    std::cout << partial.getHead() << std::endl;

    SparseMatrix state_matrix = (initial_matrix * partial);

    std::cout << state_matrix.getHead() << std::endl;
    state_matrix.print();
}
