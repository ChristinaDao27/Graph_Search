//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
//Title: mytest.cpp
//Author: Christina Dao
//Date: 10/4/2021
//Description: This file is essentially my projects' driver which
//             calls for all the required tests of my program
//E-mail: cdao1@umbc.edu
//Course Section: CMSC 341 Section 03

#include "graph.h"

class Tester{ // Tester class to implement test functions
public:

};

int main() {

    cout << "Build a graph by alternative constructor. " << endl;
    Graph aGraph("testdata.txt");
    cout << "success" << endl << endl;

    cout << "Test finding a path which does not exist in the Graph." << endl;
    aGraph.findPath(13, 4);
    cout << "Finding the path from node 13 to node 4: " << endl;
    aGraph.dump();


    cout << endl << "Test finding a path which exists in the Graph." << endl;
    aGraph.findPath(1, 14);
    cout << "Finding the path from node 1 to node 14: " << endl;
    aGraph.dump();

    cout << endl << "Test finding a path from a node to itself." << endl;
    aGraph.findPath(2, 2);
    cout << "Finding the path from node 2 to itself: " << endl;
    aGraph.dump();

    cout << endl << "Test finding a path in which the start node does not exist." << endl;
    aGraph.findPath(16, 0);
    cout << "Finding the path from node 16 to node 0: " << endl;
    aGraph.dump();

    cout << endl << "Test finding a path in which the end node does not exist." << endl;
    aGraph.findPath(0, 16);
    cout << "Finding the path from node 0 to node 16: " << endl;
    aGraph.dump();

    cout << endl << "Testing building an empty Graph object." << endl;
    Graph bGraph;
    bGraph.findPath(1, 14);
    cout << "Finding the path from node 1 to node 14 in an empty Graph object: " << endl;
    bGraph.dump();

    cout << endl << "Testing building a graph in an empty Graph object." << endl;
    bGraph.buildGraph("testdata.txt");
    bGraph.findPath(1, 14);
    cout << "Finding the path from node 1 to node 14 in graph built in empty Graph object: " << endl;
    bGraph.dump();


    cout << endl << "Testing Assignment Operator:" << endl;
    Graph copyGraph;
    copyGraph = bGraph;

    return 0;
}

