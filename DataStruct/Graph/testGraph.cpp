/*! Author：qwchen
 *! Date  : 2016-11-6
 * 测试无向图
 */

#include <iostream>
#include "Graph.h"

using namespace std;

void testGraph(){
    // test Create addEdge output
    int numberOfV = 7;
    Graph G(numberOfV);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 5);
    G.addEdge(0, 6);
    G.addEdge(3, 4);
    G.addEdge(3, 5);
    G.addEdge(4, 5);
    G.addEdge(4, 6);
    G.output();
    // test V E
    cout << "number of v : " << G.V() << endl;
    cout << "number of e : " << G.E() << endl;
    // test exitsEdge delEdge
    for (int i = 0; i <= 1; i++){
        if (G.existsEdge(0, 5)) {
            cout << "exits Edge (0, 5)" << endl;
            cout << "delete Edge (0, 5)" << endl;
            G.delEdge(0, 5);
        } else {
            cout << "Don't exits Edge (0, 5)" << endl;
        }
    }
    // test adj
    for (int i = 0; i < numberOfV; i++){
        cout << i << ": ";
        for (int t: G.adj(i)){
            cout << "(" << i << ", " << t << ") ";
        }
        cout << endl;
    }
}

void testDigraph(){

}

void testEdgeWeightedGraph(){

}

void testEdgeWeightedDigraph(){

}

int main(){
    testGraph();
    // testDigraph();
    // testEdgeWeightedGraph();
    // testEdgeWeightedDigraph();
    return 0;
}

