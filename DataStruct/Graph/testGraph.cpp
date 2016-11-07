/*! Author：qwchen
 *! Date  : 2016-11-6
 * 测试无向图
 */

#include <iostream>
#include "Graph.h"
#include "Digraph.h"

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
    // test Create addEdge output
    int numberOfV = 13;
    Digraph G(numberOfV);
    G.addEdge(4, 2);
    G.addEdge(2, 3);
    G.addEdge(3, 2);
    G.addEdge(6, 0);
    G.addEdge(0, 1);
    G.addEdge(2, 0);
    G.addEdge(11, 12);
    G.addEdge(12, 9);
    G.addEdge(9, 10);
    G.addEdge(9, 11);
    G.addEdge(8, 9);
    G.addEdge(10, 12);
    G.addEdge(11, 4);
    G.addEdge(4, 3);
    G.addEdge(3, 5);
    G.addEdge(7, 8);
    G.addEdge(8, 7);
    G.addEdge(5, 4);
    G.addEdge(0, 5);
    G.addEdge(6, 4);
    G.addEdge(6, 9);
    G.addEdge(7, 6);
    G.output();
    // test V E
    cout << "number of v : " << G.V() << endl;
    cout << "number of e : " << G.E() << endl;
    // test exitsEdge delEdge
    for (int i = 0; i <= 1; i++){
        if (G.existsEdge(10, 12)) {
            cout << "exits Edge (10, 12)" << endl;
            cout << "delete Edge (10, 12)" << endl;
            G.delEdge(10, 12);
        } else {
            cout << "Don't exits Edge (10, 12)" << endl;
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

void testEdgeWeightedGraph(){

}

void testEdgeWeightedDigraph(){

}

int main(){
    // testGraph();
    testDigraph();
    // testEdgeWeightedGraph();
    // testEdgeWeightedDigraph();
    return 0;
}

