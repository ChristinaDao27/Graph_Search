//UMBC - CSEE - CMSC 341 - Fall 2021 - Proj1
//Title: graph.cpp
//Author: Christina Dao
//Date: 10/4/2021
//Description: This file Holds the bodies of my functions for Proj1
//             and contains most of the program
//E-mail: cdao1@umbc.edu
//Course Section: CMSC 341 Section 03

#include "graph.h"

// Name: Graph (Default constructor)
// Desc: Creates a graph object which is a linked list
// Postcondition: Graph object is created
Graph::Graph(){
    m_numNodes = 0;
    m_head = nullptr;
    //Default empty string
    m_dataFile = "";
}

// Name: Graph (Overloaded Default constructor)
// Desc: Creates a graph object which is a linked list and initialized dataFile
// Postcondition: Graph object is created and data is loaded
Graph::Graph(string dataFile){
    // loadData func will give correct value to m_numNodes based on file info
    m_numNodes = 0;
    m_head = nullptr;
    m_dataFile = dataFile;
    loadData();
}

// Name: ~Graph (Destructor)
// Desc: Destructor deallocate all memory and reinitialize member variables.
// Postcondition: memory is deallocated
Graph::~Graph(){
    clearGraph();
}

// Given function.
void Graph::loadData(){
    int numNodes;
    int node, n, e, s, w;
    ifstream dataFile;
    dataFile.open(m_dataFile);
    if (dataFile.is_open()) {
        dataFile >> numNodes;
        m_numNodes = numNodes;
        for (int i = 0; i < numNodes; i++) {
            dataFile >> node >> n >> e >> s >> w;
            insert(node, n, e, s, w);
        }
    }
    else
        //the following statement provides the reason if a file doesn't open
        //please note: not all platforms are providing the same message
        cerr << "Error: " << strerror(errno) << endl;
}

// Name: insert
// Desc: This function creates nodes and insert them into the linked list.
// Postcondition: Node is created and inserted into linked list.
void Graph::insert(int node, int n, int e, int s, int w) {
    Node *tempCurr = existingNode(node);
    // update member variables by  seeing if  nodes already exist for the current
    // Node's n, e, s, w values.
    tempCurr->setNorth(existingNode(n));
    tempCurr->setEast(existingNode(e));
    tempCurr->setSouth(existingNode(s));
    tempCurr->setWest(existingNode(w));
    // Initialize visited to false
    tempCurr->setVisited(false);
    // Insert at beginning on linked list
    insertAtHead(tempCurr);
}

// Name: insertAtHead
// Desc: function inserts aNode at the head of the linked list and updates
// pointer to maintain the linked list
// Postcondition: aNode is inserted at beginning on linked list
void Graph::insertAtHead(Node * aNode){
    if (empty()){
        // m_head is initially nullptr, so must set first node to m_head
        m_head = aNode;
        aNode->setNext(nullptr);
    }
    // The node being added is not the first one
    else{
        // insert at beginning, maintain linked list
        aNode->setNext(m_head);
        m_head = aNode;
    }
}

// Name: existingNode (helper function)
// Desc: checks if memory is already allocated for a certain value and
// returns the node if so, else creates a new Node for that value.
// if value is -1, return nullptr
// Postconditions: a node for the correct value is created or found and returned, or a nullptr
Node * Graph::existingNode(int val) {
    if (val == -1){
        return nullptr;
    }
    // See if Node exists, and return that node if so
    if (findNode(val)) {
        return findNode(val);
    }
    // No existing node for the value, allocate memory for the new node and return it
    Node *newNode = new Node(val);
    newNode->setVisited(false);
    return newNode;
}


// Name: findNode(int nodeValue)
// Desc: Given a value, this function finds the node that exists for the value
// by going through the linked list as well as each nodes' n, e, s, w.
// Postcondition; the node with the right value is returned if it exists, else nullptr is returned.
Node * Graph::findNode(int nodeValue){
    if (nodeValue == -1){
        return nullptr;
    }
    //No nodes exist yet
    if (m_head == nullptr){
        return nullptr;
    }

    // Traverse through linked list. First see if the Node's value is nodeValue
    // if not, check if the node's n, e, s, w may be.
    Node *findingNode = m_head;
    while (findingNode != nullptr){
        if (findingNode->getValue() == nodeValue){
            return findingNode;
        }
        // Check if the finding node has a n, e, s, w: if it's value equals nodeValue
        // return the n, e, s, w node if it is equal.
        if (findingNode->getNorth() && findingNode->getNorth()->getValue() == nodeValue){
            return findingNode->getNorth();
        }
        if (findingNode->getEast() && findingNode->getEast()->getValue() == nodeValue){
            return findingNode->getEast();
        }
        if (findingNode->getSouth() && findingNode->getSouth()->getValue() == nodeValue){
            return findingNode->getSouth();
        }
        if (findingNode->getWest() && findingNode->getWest()->getValue() == nodeValue){
            return findingNode->getWest();
        }
        // Neither the nodes value nor the node's n, e, s, w values equal nodeValue, traverse
        findingNode = findingNode->getNext();
    }
    // No existing nodes have the value of nodeValue
    return nullptr;
}

// Name: findPath(int start, int end)
// Desc: This function checks if the start and end exists on the graph,
// otherwise there automatically is no path.
// Postcondition: true returned if a path exists between the nodes, false if not
bool Graph::findPath(int start, int end){
    // Check if graph is empty
    if (empty()) {
        return false;
    }
    Node *startNode = findNode(start);
    // No Node with start value
    if (startNode == nullptr){
        return false;
    }
    Node *endNode = findNode(end);
    // No Node with end value
    if (endNode == nullptr){
        return false;
    }
    // Both start and end exist
    // push start value onto stack
    m_path.push(startNode->getValue());
    // search for the path which may or may not exist between the two, existing nodes
    return findPath(startNode, end);
}

bool Graph::findPath(Node* aNode, int end) {
    // If entire stack has been popped, then there is no path.
    if (!m_path.empty()) {
        // Runs if path has not been achieved yet
        if (m_path.top() != end) {
            if (m_path.top() != aNode->getValue() || m_path.empty()) {
                m_path.push(aNode->getValue());
                // Check if path has been found
                if (m_path.top() == end){
                    return true;
                }
            }
            // continue search for path
            aNode->setVisited(true);

            // Recursively try all paths by checking if aNode's n, e, s, w are unvisited
            // until paths run out or path has been found
            if (aNode->getNorth() && !aNode->getNorth()->getVisited()) {
                findPath(aNode->getNorth(), end);
            } else if (aNode->getEast() && !aNode->getEast()->getVisited()) {
                findPath(aNode->getEast(), end);
            } else if (aNode->getSouth() && !aNode->getSouth()->getVisited()) {
                findPath(aNode->getSouth(), end);
            } else if (aNode->getWest() && !aNode->getWest()->getVisited()) {
                findPath(aNode->getWest(), end);
            }
            // aNode has no paths to the end
            else {
                // remove from stack
                m_path.pop();
                // recursively look for more paths while the stack has not all been popped
                if (!m_path.empty()){
                    findPath(findNode(m_path.top()), end);
                }
                // Stack is empty which means that there is no possible path
                else{
                    return false;
                }
            }
        // The top == the end which means path has been found
        } else {
            return true;
        }
    }
    return false;
}

// Name: dump
// Desc: prints out the path to the output in a specific format
// Postcondition: Path is displayed
void Graph::dump(){
    // Reverse the stack in order to display the path in the right order
    // empty m_path while doing so
    stack<int> reversedStack;
    while (!m_path.empty()){
        reversedStack.push(m_path.top());
        m_path.pop();
    }

    // Display the path
    while (!reversedStack.empty()){
        cout << reversedStack.top() << " => ";
        reversedStack.pop();
    }
    cout << "END" << endl;
    // clear visited attribute for next path to be found
    clearVisited();
}


// Name: clearResult
// Desc: clears the path found
// Postcondition: m_path is empty
void Graph::clearResult(){
    // pop stack until empty
    while (!m_path.empty()){
        m_path.pop();
    }
}

// Name: clearVisited
// Desc: resets the visited flag for all Node objects: sets m_visited to false
// Postcondition: all nodes' m_visited == false
void Graph::clearVisited(){
    // Traverse through linked list and set m_visited to false
    Node * temp = m_head;
    while (temp != nullptr){
        temp->setVisited(false);
        temp = temp->getNext();
    }
}

// Name: buildGraph
// Desc: reads a new input file and creates a new graph based on the new data
// first clears all data related to the current graph in the object
// then builds a new graph in the same object
// Postcondition: new graph with data from file is built
void Graph::buildGraph(string file){
    clearGraph();
    m_head = nullptr;
    m_dataFile = file;
    loadData();
}

// Name: clearGraph
// Desc: deallocates all memory and reinitialize all member variables
// Postcondition: graph object becomes empty
void Graph::clearGraph(){
    // Traverse through linked list and delete each node
    Node *temp = m_head;
    while (temp != nullptr){
        temp = temp->getNext();
        delete m_head;
        m_head = temp;
    }
    // deletes last existing node
    delete m_head;

    // reinitialize member variables
    m_head = nullptr;
    m_numNodes = 0;
    m_dataFile = "";

    clearResult();
    clearVisited();
}

// Name: Graph::operator= (assignment operator function)
// Desc: Creates a deep copy of rhs.
// Postcondition; deep copy of rhs is created.
const Graph & Graph::operator=(const Graph & rhs){
    if (this != &rhs){
        // Deallocate memory of this/LHS
        this->clearGraph();
        // Using the same data text file as RHS, build a new graph.
        this->buildGraph(rhs.m_dataFile);
    }

    // This block of codes displays proof that my assignment operator works
    Node *tempThis = this->m_head;
    Node *tempRHS = rhs.m_head;
    // Display memory location and value of each node in both the RHS and LHS graphs
    // Memory locations will be different but values will be the same.
    for (int i = 0; i < m_numNodes; i++){
        cout << "copyGraph Memory Location:   " << tempThis;
        cout << "    copyGraph Value: " << tempThis->getValue() << endl;
        cout << "aGraph Memory Location:      " << tempRHS;
        cout << "    aGraph Value:    " << tempRHS->getValue() << endl << endl;
        // Traverse through linked lists
        tempThis = tempThis->getNext();
        tempRHS = tempRHS->getNext();
    }
    return *this;
}

// Name; empty (given)
// Desc: checks if graph is empty or not
bool Graph::empty() const		// is the list empty?
{ return m_head == nullptr; }