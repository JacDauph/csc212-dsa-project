# CSC 212 DSA Project

Group Members: Alex Chow, Jacob Dauphinais, Kevin Lattuada, Peter Majdalani

## Summary

This project is an application that can predict future outcomes of traffic routes based on the current state of a matrix using Markov Chains. Markov chains are essentially graphs of nodes represented inside of a matrix in which each matrix entry denotes a specific probability that something will travel to the other specified node. 

## Before trying to run any code, make sure you are able to use g++. In order to install please follow the directions from the gcc website: 
[GCC website](https://gcc.gnu.org/install/) 

[Installing GCC Binaries instructions](https://gcc.gnu.org/install/binaries.html)
# **Compilation Time Instructions:**
### The .txt file is the dataset used, where *name* can be any .txt file name with the similar dataset content.

## With CLion
1. Open CLion
2. Create a new project with C++11
3. Add the main.cpp, other .cpp files,the .h files, and desired .txt files to your project.
## Make sure the .txt file is within cmake-build-debug and within the file of testing in there. The main.cpp should replace the old main and the new files should be added in the same area as the main.cpp

4. Under CMakeList.txt make sure the add_executable is *"add_executable(prog main.cpp SparseMatrix.cpp SparseMatrix.h SparseNode.cpp SparseNode.h)"*
5. If the program is going to be ran automatically, over in "Open 'Edit/Debug configurations' dialog" click edit configurations
6. Inside Program Arguments add in the name of your text file. For example: (name.txt)
7. Click the run program button.

## If not using CLion
1. Open up your IDE
2. Create a new Project
3. Add all the files to your program
4.  Inside the terminal enter: *g++ main.cpp SparseMatrix.cpp SparseNode.cpp -o prog* 
5.  After : *./prog name.txt*
6.  Or: *g++ main.cpp SparseMatrix.cpp SparseNode.cpp -o prog && ./prog name.txt*

1. * Or: *g++ -std=c++11 main.cpp SparseMatrix.cpp SparseNode.cpp -o prog*
2. *./prog name.txt*


### "name" can be substituted with the name of the file for testing.
