//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
//Title: graph.h
//Author: Christina Dao
//Date: 10/4/2021
//Description: This file is the header file for my project 1
//E-mail: cdao1@umbc.edu
//Course Section: CMSC 341 Section 03

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <cstring>
using namespace std;
class Grader;
class Tester;
class Graph;
class Node{
public:
    friend class Grader;
    friend class Tester;
    friend class Graph;
    Node():m_value(0), m_visited(false), m_next(nullptr),
           m_north(nullptr),m_east(nullptr),m_south(nullptr),m_west(nullptr){}
    Node(int v):m_value(v), m_visited(false), m_next(nullptr),
                m_north(nullptr),m_east(nullptr),m_south(nullptr),m_west(nullptr){}
    Node(int v, Node* n, Node* e, Node* s, Node* w):
            m_value(v),m_north(n),m_east(e),m_south(s),m_west(w){}
    ~Node(){}
    void setValue(int aValue){m_value = aValue;}
    int getValue(){return m_value;}
    void setVisited(bool visited){m_visited = visited;}
    bool getVisited(){return m_visited;}
    void setNorth(Node * aNode){m_north = aNode;}
    Node * getNorth(){return m_north;}
    void setSouth(Node * aNode){m_south = aNode;}
    Node * getSouth(){return m_south;}
    void setEast(Node * aNode){m_east = aNode;}
    Node * getEast(){return m_east;}
    void setWest(Node * aNode){m_west = aNode;}
    Node * getWest(){return m_west;}
    void setNext(Node * aNode){m_next=aNode;}
    Node * getNext(){return m_next;}
private:
    int m_value;//stores the node number
    bool m_visited;
    Node * m_next;
    Node * m_north;
    Node * m_east;
    Node * m_south;
    Node * m_west;
};

class Graph{
public:
    friend class Grader;
    friend class Tester;
    Graph();
    Graph(string dataFile);// read data from a file and initialize the object
    ~Graph();// destructor
    bool findPath(int start, int end);// find a path from start to end nodes
    void dump();// print the path found from start to end nodes
    void buildGraph(string file);// construct a new graph from the file
    const Graph & operator=(const Graph & rhs);// overloaded assignment operator
    bool empty() const;// is the list empty?
private:
    int m_numNodes;//number of nodes in the graph
    Node * m_head;//the head node of the linked list
    string m_dataFile;
    stack <int> m_path;//to store the search result, i.e. the path

    void loadData();//read data from file and initialize all member variables
    void insert(int node, int n, int e, int s, int w);
    bool findPath(Node* aNode, int end);//helper function for recursive calls
    void clearResult();//clear the stack storing the result, i.e. path
    void clearVisited();//reset visited flag of all nodes
    void clearGraph();//delete all memory and reset all member variables
    Node * findNode(int nodeValue);//traverses the list and finds a node
    void insertAtHead(Node * aNode);//insert a node at the head od list

    // ***************************************************
    // Any private helper functions must be declared here!
    // ***************************************************
    Node * existingNode(int val); // finds a node with value v, if there isn't one,
                                  // allocate memory for it/ make a new node
};