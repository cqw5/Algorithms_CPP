/*! Author：qwchen
 *! Date  : 2016-11-6
 * 无向图
 */

#ifndef Graph_
#define Graph_

#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int num_v);
    ~Graph();
    int V() const;                       // 返回图的结点数
    int E() const;                       // 返回图的边数
    bool existsEdge(int v, int w) const; // 判断边是否存在
    void addEdge(int v, int w);          // 添加边
    void delEdge(int v, int w);          // 删除边
    vector<int>& adj(int v);             // 返回结点v的邻接数组
    void output();                       // 打印图

private:
    int num_v_;         // 图的结点数
    int num_e_;         // 图的边数 
    vector<int> *adj_;  // 图的邻接数组
    void checkIndex(int v) const; // 检查节点是否存在
};

Graph::Graph(int num_v) {
    if (num_v < 0) {
        stringstream s;
        s << "number of vertices must be >= 0" << endl;
        throw range_error(s.str());
    }
    num_v_ = num_v;
    num_e_ = 0;
    adj_ = new vector<int>[num_v];
}

Graph::~Graph(){
    delete []adj_;
}

int Graph::V() const {
    return num_v_;
}

int Graph::E() const {
    return num_e_;
}

void Graph::checkIndex(int v) const {
    if (v < 0 || v >= num_v_) {
        stringstream s;
        s << v <<" is not a permissible node" << endl;
        throw range_error(s.str());
    }
}

bool Graph::existsEdge(int v, int w) const {
    checkIndex(v);
    checkIndex(w);
    for (int t : adj_[v]) {
        if (t == w) return true;
    }
    return false;
}

void Graph::addEdge(int v, int w) {
    checkIndex(v);
    checkIndex(w);
    adj_[v].push_back(w);
    adj_[w].push_back(v);
    num_e_++;
}

void Graph::delEdge(int v, int w) {
    checkIndex(v);
    checkIndex(w);
    for (auto t = adj_[v].begin(); t != adj_[v].end(); t++){
        if (*t == w){
            adj_[v].erase(t);
            break;
        }
    }
    for (auto t = adj_[w].begin(); t != adj_[w].end(); t++){
        if (*t == v){
            adj_[w].erase(t);
            break;
        }
    }
    num_e_--;
}

vector<int>& Graph::adj(int v) {
    return adj_[v];
}

void Graph::output(){
    for (int i = 0; i < num_v_; i++){
        cout << i << ": ";
        for (int t: adj_[i]){
            cout << "(" << i << ", " << t << ") ";
        }
        cout << endl;
    }
}

#endif
