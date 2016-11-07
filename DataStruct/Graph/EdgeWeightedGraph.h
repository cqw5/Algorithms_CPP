/*! Author：qwchen
 *! Date  : 2016-11-7
 * 加权无向图
 */

#ifndef EdgeWeightedGraph_
#define EdgeWeightedGraph_

#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// 加权无向边
class Edge {
public:
    Edge(){}
    Edge(int v, int w, double weight){ v_ = v; w_ = w; weight_ = weight; }
    int v() const { return v_; }
    int w() const { return w_; }
    double weight() const { return weight_; }
    operator double() const { return weight_; }  // 通过变得权来比较边的大小
private:
    int v_;         // 顶点
    int w_;         // 另一个顶点
    double weight_; // 边的权重
};


// 加权无向图的类
class EdgeWeightedGraph {
public:
    EdgeWeightedGraph(int num_v);
    ~EdgeWeightedGraph();
    int V() const;                             // 返回图的结点数
    int E() const;                             // 返回图的边数
    bool existsEdge(int v, int w) const;       // 判断边是否存在
    void addEdge(int v, int w, double weight); // 添加边
    void delEdge(int v, int w);                // 删除边
    vector<Edge>& adj(int v) const;            // 返回结点v的邻接数组
    vector<Edge> edges() const;                // 返回图的所有边，与adj不同，all_edges是局部变量，不能返回引用
    void output() const;                       // 打印图

private:
    int num_v_;         // 图的结点数
    int num_e_;         // 图的边数 
    vector<Edge> *adj_; // 图的邻接数组
    void checkIndex(int v) const; // 检查节点是否存在
};

EdgeWeightedGraph::EdgeWeightedGraph(int num_v) {
    if (num_v < 0) {
        stringstream s;
        s << "number of vertices must be >= 0" << endl;
        throw range_error(s.str());
    }
    num_v_ = num_v;
    num_e_ = 0;
    adj_ = new vector<Edge>[num_v_];
}

EdgeWeightedGraph::~EdgeWeightedGraph() {
    delete []adj_;
}

void EdgeWeightedGraph::checkIndex(int v) const {
    if (v < 0 || v >= num_v_) {
        stringstream s;
        s << v <<" is not a permissible node" << endl;
        throw range_error(s.str());
    }
}

int EdgeWeightedGraph::V() const {
    return num_v_;
}

int EdgeWeightedGraph::E() const {
    return num_e_;
}

bool EdgeWeightedGraph::existsEdge(int v, int w) const {
    checkIndex(v);
    checkIndex(w);
    for (Edge e: adj_[v]){
        if (e.w() == w) return true;
    }
    return false;
}

void EdgeWeightedGraph::addEdge(int v, int w, double weight) {
    checkIndex(v);
    checkIndex(w);
    adj_[v].push_back(Edge(v, w, weight));
    adj_[w].push_back(Edge(w, v, weight));
       num_e_++;
}

void EdgeWeightedGraph::delEdge(int v, int w) {
    checkIndex(v);
    checkIndex(w);
    for(auto e = adj_[v].begin(); e != adj_[v].end(); e++){
        if (e->w() == w){
            adj_[v].erase(e);
            break;
        }
    }
    for(auto e = adj_[w].begin(); e != adj_[w].end(); e++){
        if (e->v() == v){
            adj_[w].erase(e);
            break;
        }
    }
    num_e_--;
}

vector<Edge>& EdgeWeightedGraph::adj(int v) const {
    return adj_[v];
} 

vector<Edge> EdgeWeightedGraph::edges() const {
    vector<Edge> all_Edges;
    for (int i = 0; i < num_v_; i++) {  // 遍历每个顶点
        for (Edge e: adj_[i]) {         // 对每个顶点遍历每条边
            if (e.v() < e.w()) {        // 取v < w的边，防止无向图的边被取两次
                all_Edges.push_back(e);
            }
        }
    }
    return all_Edges;
}

void EdgeWeightedGraph::output() const {
    for (int i = 0; i < num_v_; i++){
        cout << i << " : ";
        for (Edge e: adj_[i]){
            cout << "(" << e.v() << ", " << e.w() << ", " << e.weight() << ") ";
        }
        cout << endl;
    }
}

#endif