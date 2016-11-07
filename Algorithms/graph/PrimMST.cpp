/*! Author：qwchen
 *! Date  : 2016-11-7
 * 加权无向图的最小生成树：Prim算法
 * 思路：一开始生成树只有一个顶点，然后向它添加V-1条边，每次总是将下一条连接树中的顶点与不在树中的顶点且权重最小的切分边加入树中。
 * 方法：用marked数组标记已经在树中的结点
 *       用数组mst存放生成树的边
 *       用小顶堆minheap保存候选的横切边
 */

#include <iostream>
#include <vector>
#include <queue>
#include "../../DataStruct/Graph/EdgeWeightedGraph.h"

using namespace std;

class PrimMST {
public:
    PrimMST(EdgeWeightedGraph& G);  // Prim算法
    vector<Edge>& mst();            // 返回Prim算法生成的最小生成树

private:
    vector<bool> marked_;                                        // 是否存在最小生成树，true表示存在
    vector<Edge> mst_;                                           // 保存最小生成树的数组
    priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap_;  // 存放横切边
    void visit(EdgeWeightedGraph& G, int v);                     // 标记顶点v并将所有连接v和未标记顶点的边加入minHeap_
};

PrimMST::PrimMST(EdgeWeightedGraph& G){
    marked_.assign(G.V(), false);
    visit(G, 0);
    while(!minHeap_.empty()){
        Edge e = minHeap_.top(); // 取出权重最小的边
        minHeap_.pop();
        int v = e.v();
        int w = e.w();
        if (marked_[v] && marked_[w]) continue; // 若边的两个端点都在生成树中，则该边无效，否则将该边放到最小生成树中
        mst_.push_back(e); // 将边加入到生成树中
        if (!marked_[v]) visit(G, v);
        if (!marked_[w]) visit(G, w);
    }
}

void PrimMST::visit(EdgeWeightedGraph& G, int v){
    marked_[v] = true;       // 标记顶点v
    for(Edge e: G.adj(v)){   // 将所有连接v并且未被标记的边加入minHeap_
        if(!marked_[e.w()]) {
            minHeap_.push(e);
        }
    }
}

vector<Edge>& PrimMST::mst(){
    return mst_;
}


void testPrim(){
    EdgeWeightedGraph G(8);
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
    PrimMST prim(G);
    vector<Edge> mst = prim.mst();
    if (!mst.empty()) {
        cout << "[Success]" << endl;
        for (Edge e: mst){
            cout << "(" << e.v() << ", " << e.w() << ", " << e.weight() << ")" << endl;
        }
    } else {             // 不存在最小生成树
        cout << "[Failed]" << endl;
    }
}

int main(){
    testPrim();
    return 0;
}





