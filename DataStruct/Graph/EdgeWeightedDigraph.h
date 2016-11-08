/*! Author：qwchen
 *! Date  : 2016-11-8
 * 加权有向图
 */

#ifndef EdgeWeightedDigraph_
#define EdgeWeightedDigraph_

#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// 加权无向边
class DirectedEdge {
public:
    DirectedEdge(){}
    DirectedEdge(int v, int w, double weight){ v_ = v; w_ = w; weight_ = weight; }
    int from() const { return v_; }
    int to() const { return w_; }
    double weight() const { return weight_; }
    operator double() const { return weight_; }  // 通过变得权来比较边的大小
private:
    int v_;         // 边的起点
    int w_;         // 边的终点
    double weight_; // 边的权重
};


// 加权无向图的类
class EdgeWeightedDigraph {
public:
    EdgeWeightedDigraph(int num_v);
    ~EdgeWeightedDigraph();
    int V() const;                             // 返回图的结点数
    int E() const;                             // 返回图的边数
    bool existsEdge(int v, int w) const;       // 判断边是否存在
    void addEdge(int v, int w, double weight); // 添加边
    void delEdge(int v, int w);                // 删除边
    vector<DirectedEdge>& adj(int v) const;    // 返回结点v的邻接数组
    vector<DirectedEdge> edges() const;        // 返回图的所有边，与adj不同，allEdges是局部变量，不能返回引用
    void output() const;                       // 打印图

private:
    int num_v_;         // 图的结点数
    int num_e_;         // 图的边数 
    vector<DirectedEdge> *adj_;   // 图的邻接数组
    void checkIndex(int v) const; // 检查顶点是否存在
};

EdgeWeightedDigraph::EdgeWeightedDigraph(int num_v) {
    if (num_v < 0) {
        stringstream s;
        s << "number of vertices must be >= 0" << endl;
        throw range_error(s.str());
    }
    num_v_ = num_v;
    num_e_ = 0;
    adj_ = new vector<DirectedEdge>[num_v_];
}

EdgeWeightedDigraph::~EdgeWeightedDigraph() {
    delete []adj_;
}

void EdgeWeightedDigraph::checkIndex(int v) const {
    if (v < 0 || v >= num_v_) {
        stringstream s;
        s << v <<" is not a permissible node" << endl;
        throw range_error(s.str());
    }
}

int EdgeWeightedDigraph::V() const {
    return num_v_;
}

int EdgeWeightedDigraph::E() const {
    return num_e_;
}

bool EdgeWeightedDigraph::existsEdge(int v, int w) const {
    checkIndex(v);
    checkIndex(w);
    for (DirectedEdge e: adj_[v]){
        if (e.to() == w) return true;
    }
    return false;
}

void EdgeWeightedDigraph::addEdge(int v, int w, double weight) {
    checkIndex(v);
    checkIndex(w);
    adj_[v].push_back(DirectedEdge(v, w, weight));
    num_e_++;
}

void EdgeWeightedDigraph::delEdge(int v, int w) {
    checkIndex(v);
    checkIndex(w);
    for(auto e = adj_[v].begin(); e != adj_[v].end(); e++){
        if (e->to() == w){
            adj_[v].erase(e);
            break;
        }
    }
    num_e_--;
}

vector<DirectedEdge>& EdgeWeightedDigraph::adj(int v) const {
    return adj_[v];
} 

vector<DirectedEdge> EdgeWeightedDigraph::edges() const {
    vector<DirectedEdge> allEdges;
    for (int i = 0; i < num_v_; i++) {  // 遍历每个顶点
        for (DirectedEdge e: adj_[i]) { // 对每个顶点遍历每条边
            allEdges.push_back(e);
        }
    }
    return allEdges;
}

void EdgeWeightedDigraph::output() const {
    for (int i = 0; i < num_v_; i++){
        cout << i << " : ";
        for (DirectedEdge e: adj_[i]){
            cout << "(" << e.from() << ", " << e.to() << ", " << e.weight() << ") ";
        }
        cout << endl;
    }
}

#endif