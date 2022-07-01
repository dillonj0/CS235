//
// Created by Dillon Jensen on 6/30/22.
//

#include <fstream>
#include "Navigation.h"

using namespace std;

    Navigation::Navigation(){
        cout << endl;
        cout << "Starting calculation ... " << endl;
    }
    Navigation::~Navigation() {
        cout << "  ... Process ended." << endl;
    }

    // This function reads in the contents of the file _mapName.
    // The function can assume that the contents of the specified conform with the specs given in the README.txt file
    // Returns true if the file is read in successfully, false otherwise.
//      From the class definition:
//        private:
//        vector <vector <int> > theCosts;
//        int numNodes;
//        //We'll fill these guys as we read from the input
//        // file: the adjacency matrix & dimension.
    bool Navigation::readNetwork(string _mapName) {
//        cout << "I'm trying to read from file \"" << _mapName << "\"." << endl;
        int firstLine;
        ifstream inFile;
        inFile.open(_mapName);

        inFile >> firstLine;
//        cout << "Vector dimension = " << firstLine << endl; //
        numNodes = firstLine;

        if(inFile.is_open()){
            cout << "Reading file ... " << endl;
            // cin N items, store in vector.
            // ---> store vector in vector of vectors
            // repeat N times.
            for (int i = 0; i < firstLine; i++){
                vector <int> currentLine;
                for (int j = 0; j < firstLine; j++){
                    int newCost;

                    inFile >> newCost;
                    currentLine.push_back(newCost);
                }

//                // for debugging:
//                cout << "Adding to read file: ";
//                for (int m = 0; m < firstLine; m++){
//                    cout << currentLine[m] << " ";
//                }
//                cout << endl; //

                theCosts.push_back((currentLine));
            }
//            cout << "File read success!" << endl;
            inFile.close();
            return true;
        }
        else{
            cout << "Could not open file." << endl;
            inFile.close();
            return false;
        }
    }

// in map1.txt, solveMap(13, 1) should return the shortest path from node 13 to node 1, which is:
//      13, 9, 10, 7, 3, 2, 1

    queue<int> Navigation::computeShortestPath(int _startInd, int _endInd){
        cout << "Computing shortest path from " << _startInd << " to " << _endInd << " ... " << endl;

        queue<int> thePath;
//    (1)   PriorityQueue<Node> PQ (see programming hint 2)
        priority_queue<Node, vector<Node>, Node> cheapPQ;
//    (2)   Create Node n, with n.cost = 0 and n.path = <A> (see programming hint 1)
        Node n;
        n.cost = 0;
        n.path.push(_startInd);
//    (3)   Insert Node n into PQ
        cheapPQ.push(n);

//    (4)   Loop while the top Node in PQ does not contain a path that ends
//          in the destination
        while (cheapPQ.top().path.back() != _endInd){
//        (5)   Pop the top item off the priority queue and store it in
//                  current (see programming hint 3)
//                      "top()" to store, then
//                      "pop()" to delete top item
                Node current = cheapPQ.top();
                cheapPQ.pop();
//        (6)   Set last to be the last destination in current.path (see programming
//                  hint 4)
//                  "back()" accesses the most recently inserted item.
//                  ---> This is helpful because all these nodes are queues.
                int last = current.path.back();
//        (7)   For each neighbor j of last (i.e., Cost(last,j) > 0), insert a
//                  new Node (denoted nn) into PQ in which
//                  nn.cost = current.cost+Cost(last,j) and
//                  nn.path = concat(current.path, j)
                for (int i = 0; i < numNodes; i++){
                    if (theCosts[last][i] > 0){
                        Node nn;
                        nn.cost = current.cost + theCosts[last][i];
                        nn.path = current.path;
                        nn.path.push(i);
                        cheapPQ.push(nn);
                    }
                }
              }
//    (8)   Return the path (which is a queue of integers) of the top Node in PQ
        thePath = cheapPQ.top().path;
//        cout << "Optimal path calculated." << endl;
        cheapestCost = cheapPQ.top().cost;
        return thePath;
    }

    // prints out to the console the path stored in _path
    void Navigation::printPath(queue<int> _path) {
        cout << "========================" << endl;
        cout << "Optimal path:" << endl;
        int len = _path.size();

        //print the path:
        for (int i = 0; i < len; i++){
            cout << _path.front();
            _path.pop();
            if (i < len-1){
                cout << " -> ";
            }
        }
        cout << endl;

        //print the cost:
        cout << "Cost: " << cheapestCost << endl;
        cout << "========================" << endl;
    }