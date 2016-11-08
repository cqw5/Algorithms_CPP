/*! Author：qwchen
 *! Date  : 2016-11-8
 * 测试无向图、有向图、加权无向图、加权有向图
 */

#include <iostream>
#include "Graph.h"
#include "Digraph.h"
#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDigraph.h"

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
    int numberOfV = 8;
    EdgeWeightedGraph G(numberOfV);
    G.addEdge(4, 5, 0.35);
    G.addEdge(4, 7, 0.37);
    G.addEdge(5, 7, 0.28);
    G.addEdge(0, 7, 0.16);
    G.addEdge(1, 5, 0.32);
    G.addEdge(0, 4, 0.38);
    G.addEdge(2, 3, 0.17);
    G.addEdge(1, 7, 0.19);
    G.addEdge(0, 2, 0.26);
    G.addEdge(1, 2, 0.36);
    G.addEdge(1, 3, 0.29);
    G.addEdge(2, 7, 0.34);
    G.addEdge(6, 2, 0.40);
    G.addEdge(3, 6, 0.52);
    G.addEdge(6, 0, 0.58);
    G.addEdge(6, 4, 0.93);
    G.output();
    // test V E
    cout << "number of v : " << G.V() << endl;
    cout << "number of e : " << G.E() << endl;
    // test exitsEdge delEdge
    for (int i = 0; i <= 1; i++){
        if (G.existsEdge(0, 7)) {
            cout << "exits Edge (0, 7)" << endl;
            cout << "delete Edge (0, 7)" << endl;
            G.delEdge(0, 7);
        } else {
            cout << "Don't exits Edge (0, 7)" << endl;
        }
    }
    // test adj
    for (int i = 0; i < numberOfV; i++){
        cout << i << ": ";
        for (Edge e: G.adj(i)){
            cout << "(" << e.v() << ", " << e.w() << ", " << e.weight() <<") ";
        }
        cout << endl;
    }
    // test Edges
    vector<Edge> allEdges = G.edges();
    for (int i = 0; i < allEdges.size(); i++){
        cout << "Edge" << i << ": (" << allEdges[i].v() << ", " << allEdges[i].w() << ", " << allEdges[i].weight() << ")" << endl; 
    }
}

void testEdgeWeightedDigraph(){
    int numberOfV = 8;
    EdgeWeightedDigraph G(8);
    G.addEdge(4, 5, 0.35);
    G.addEdge(5, 4, 0.35);
    G.addEdge(4, 7, 0.37);
    G.addEdge(5, 7, 0.28);
    G.addEdge(7, 5, 0.28);
    G.addEdge(5, 1, 0.32);
    G.addEdge(0, 4, 0.38);
    G.addEdge(0, 2, 0.26);
    G.addEdge(7, 3, 0.39);
    G.addEdge(1, 3, 0.29);
    G.addEdge(2, 7, 0.34);
    G.addEdge(6, 2, 0.40);
    G.addEdge(3, 6, 0.52);
    G.addEdge(6, 0, 0.58);
    G.addEdge(6, 4, 0.93);
    G.output();
    // test V E
    cout << "number of v : " << G.V() << endl;
    cout << "number of e : " << G.E() << endl;
    // test exitsEdge delEdge
    for (int i = 0; i <= 1; i++){
        if (G.existsEdge(6, 4)) {
            cout << "exits Edge (6, 4)" << endl;
            cout << "delete Edge (6, 4)" << endl;
            G.delEdge(6, 4);
        } else {
            cout << "Don't exits Edge (6, 4)" << endl;
        }
    }
    // test adj
    for (int i = 0; i < numberOfV; i++){
        cout << i << ": ";
        for (DirectedEdge e: G.adj(i)){
            cout << "(" << e.from() << ", " << e.to() << ", " << e.weight() <<") ";
        }
        cout << endl;
    }
    // test Edges
    vector<DirectedEdge> allEdges = G.edges();
    for (int i = 0; i < allEdges.size(); i++){
        cout << "Edge" << i << ": (" << allEdges[i].from() << ", " << allEdges[i].to() << ", " << allEdges[i].weight() << ")" << endl; 
    }
}

int main(){
    testGraph();
    testDigraph();
    testEdgeWeightedGraph();
    testEdgeWeightedDigraph();
    return 0;
}

