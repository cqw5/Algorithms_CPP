/*! Author：qwchen
 *! Date  : 2016-11-7
 * 加权无向图的最小生成树：Kruskal算法
 * 思路：使用贪心的方法。将图的所有边放入小顶堆中，不断选择一条成本最小且不会产生环路的边加入生成树中，直到树中含有V-1条边为止
 * 方法：用数组mst存放生成树的边
 *       用小顶堆minheap保存候选的边，初始minheap为包含所有边的小顶堆
 *       通过查并集来判断找到的边是否是有效边(即不会构成环)
 */

#include <iostream>
#include <vector>
#include <queue>
#include "../../DataStruct/UnionFind/unionFind.h"
#include "../../DataStruct/Graph/EdgeWeightedGraph.h"

using namespace std;

class KruskalMST {
public:
    KruskalMST(EdgeWeightedGraph& G);  // KruskalMST算法
    vector<Edge>& mst();               // 返回Kruskal算法产生的最小生成树

private:
    priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap_;  // 用一个小顶堆来保存图中所有的边
    vector<Edge> mst_;                                           // 保存最小生成树的数组
};

KruskalMST::KruskalMST(EdgeWeightedGraph& G){
    for(auto e: G.edges()){
        minHeap_.push(e);  
    }
    unionFind uf(G.V());         // 查并集类
    while (!minHeap_.empty()) {  // 还存在边
        // 贪心法：取出权重最小的边
        Edge e = minHeap_.top();
        minHeap_.pop();
        // 若加入权重最小的边后生成树不会产生环，则将边加入到生成树中
        // 查找边的两个顶点的集合id
        //     若集合id相同，则向生成树中加入该边会形成环，不加入
        //     若集合id不相同，则向生成树中加入该边不会形成环，加入；然后将两个集合合并
        int class_v = uf.find(e.v());
        int class_w = uf.find(e.w());
        if (class_v != class_w) {
            mst_.push_back(e);
            uf.unite(class_v, class_w);
        }
    }
}

vector<Edge>& KruskalMST::mst(){
    return mst_;
}


void testKruskal(){
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
    KruskalMST kruskal(G);
    vector<Edge> mst = kruskal.mst();
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
    testKruskal();
    return 0;
}


