/*！
 * 加权无向图的最小生成树：Kruskal算法
 * 思路：使用贪心的方法。将图的所有边放入小顶堆中，不断选择一条成本最小且不会产生环路的边加入生成树中，直到树中含有V-1条边为止
 * 方法：用数组mst存放生成树的边
 *       用小顶堆minheap保存候选的边，初始minheap为包含所有边的小顶堆
 *       通过查并集来判断找到的边是否是有效边(即不会构成环)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "../search/unionFind.h"

using namespace std;

// 加权无向边的类
class edge{
public:
    edge(){}
    edge(int v, int w, double weight){ v_ = v; w_ = w; weight_ = weight; }
    int v() const { return v_; }
    int w() const { return w_; }
    double weight() const { return weight_; }
    operator double() const { return weight_; }
private:
    int v_;         // 顶点
    int w_;         // 另一个顶点
    double weight_; // 边的权重
};

// 加权无向图的类
class Graph {
public:
    Graph(int num_v);
    ~Graph();
    void addEdge(int v, int w, double weight); // 添加边
    int V() const;                             // 返回图的结点数
    vector<edge> edges() const;                // 返回图的所有边
private:
    int num_v_;         // 图的结点数
    vector<edge> *adj_; // 图的邻接数组
};

Graph::Graph(int num_v) {
    num_v_ = num_v;
    adj_ = new vector<edge>[num_v_];
}

Graph::~Graph() {
    delete []adj_;
}

void Graph::addEdge(int v, int w, double weight) {
    adj_[v].push_back(edge(v, w, weight));
    adj_[w].push_back(edge(w, v, weight));
}

int Graph::V() const {
    return num_v_;
}

vector<edge> Graph::edges() const {
    vector<edge> all_edges;
    for (int i = 0; i < num_v_; i++) {  // 遍历每个顶点
        for (edge e: adj_[i]) {         // 对每个顶点遍历每条边
            if (e.v() < e.w()) {        // 取v < w的边，防止无向图的边被取两次
                all_edges.push_back(e);
            }
        }
    }
    return all_edges;
}

/*
 * parament:
 *     G: 加权无向图
 *     mst：保存最小生成树的数组
 * return:
 *     bool: 是否存在最小生成树，true表示存在
 *     mst: 保存最小生成树的数组
 */
bool kruskal(Graph G, vector<edge> &mst){
    int n = G.V();
    vector<edge> minheap(G.edges());  // 用一个小顶堆来保存图中所有的边
    make_heap(minheap.begin(), minheap.end(), greater<double>());
    unionFind uf(n);                  // 查并集类
    while (!minheap.empty()) {        // 还存在边
        // 取出权重最小的边
        edge e = minheap.front();
        pop_heap(minheap.begin(), minheap.end(), greater<double>()); minheap.pop_back();
        // 若加入权重最小的边后生成树不会产生环，则将边加入到生成树中
        // 查找边的两个顶点的集合id
        //     若集合id相同，则向生成树中加入该边会形成环，不加入
        //     若集合id不相同，则向生成树中加入该边不会形成环，加入；然后将两个集合合并
        int class_v = uf.find(e.v());
        int class_w = uf.find(e.w());
        if (class_v != class_w) {
            mst.push_back(e);
            uf.unite(class_v, class_w);
        }
    }
    return mst.size() == (n - 1);
}


void testKruskal(){
    Graph G(8);
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
    vector<edge> mst;
    if(kruskal(G, mst)){ // 存在最小生成树
        cout << "[Success]" << endl;
        for (edge e: mst){
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


