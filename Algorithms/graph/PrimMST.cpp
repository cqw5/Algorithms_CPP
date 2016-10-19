/*！
 * 加权无向图的最小生成树：Prim算法
 * 思路：一开始生成树只有一个顶点，然后向它添加V-1条边，每次总是将下一条连接树中的顶点与不在树中的顶点且权重最小的切分边加入树中。
 * 方法：用marked数组标记已经在树中的结点
 *       用数组mst存放生成树的边
 *       用小顶堆minheap保存候选的切分边
 */

#include <iostream>
#include <vector>
#include <algorithm>

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
    vector<edge> adj(int v) const;             // 返回顶点v的邻接边
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

vector<edge> Graph::adj(int v) const{
    return adj_[v];
}

// 标记顶点v并将所有连接v和未标记顶点的边加入小顶堆
void visit(Graph G, vector<edge> &minheap, vector<bool> &marked, int v){
    marked[v] = true;
    for (edge e: G.adj(v)){
        if (marked[e.v()] && marked[e.w()]) continue;
        minheap.push_back(e); push_heap(minheap.begin(), minheap.end(), greater<double>());
    }
}

/*
 * parament:
 *     G: 加权无向图
 *     mst：保存最小生成树的数组
 * return:
 *     bool: 是否存在最小生成树，true表示存在
 *     mst: 保存最小生成树的数组
 */
bool prim(Graph G, vector<edge> &mst){
    int n = G.V();
    vector<bool> marked(n, false);  // 标记已经在树中的结点
    vector<edge> minheap;           // 小顶堆，用来保存切分边
    make_heap(minheap.begin(), minheap.end(), greater<double>());
    visit(G, minheap, marked, 0);
    while(!minheap.empty()) {       // 还存在边
        // 取出权重最小的边
        edge e = minheap.front();
        pop_heap(minheap.begin(), minheap.end(), greater<double>()); minheap.pop_back();
        int v = e.v();
        int w = e.w();
        // 若边的两个端点都在生成树中，则该边无效，否则将该边放到最小生成树中
        if (marked[v] && marked[w]) continue;
        mst.push_back(e);
        if (!marked[v]) visit(G, minheap, marked, v);
        if (!marked[w]) visit(G, minheap, marked, w);
    }
    return mst.size() == (n - 1);
}



void testPrim(){
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
    if(prim(G, mst)){ // 存在最小生成树
        cout << "[Success]" << endl;
        for (edge e: mst){
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





