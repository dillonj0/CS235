#include <iostream>
#include <queue>
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
//    (1)   PriorityQueue<Node> PQ (see programming hint 2)
//                priority_queue<int> myPriorityQueue;
//    ------>     priority_queue<Node, vector<Node>, Node> myPriorityQueue;
//
//    (2)   Create Node n, with n.cost = 0 and n.path = <A> (see programming hint 1)
//                struct Node {
//                    int cost;
//                    queue<int> path;
//
//                    bool operator() (Node const& n1, Node const& n2) {
//                        return n1.cost > n2.cost;
//                    }
//                };
//
//    (3)   Insert Node n into PQ
//    (4)   Loop while the top Node in PQ does not contain a path that ends
//          in the destination
//          //    while ((PQ.top()).back()
//    {
//        (5)   Pop the top item off the priority queue and store it in
//                  current (see programming hint 3)
//                      "top()" to store, then
//                      "pop()" to delete top item
//        (6)   Set last to be the last destination in current.path (see programming
//                  hint 4)
//                  "back()" accesses the most recently inserted item.
//                  ---> This is helpful because all these nodes are queues.
//        (7)   For each neighbor j of last (i.e., Cost(last,j) > 0), insert a
//                  new Node (denoted nn) into PQ in which
//                  nn.cost = current.cost+Cost(last,j) and
//                  nn.path = concat(current.path, j)
//      }
//    (8)   Return the path (which is a queue of integers) of the top Node in PQ
    return 0;
}