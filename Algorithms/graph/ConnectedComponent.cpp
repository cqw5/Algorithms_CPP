/*! Author：qwchen
 *! Date  : 2016-11-6
 * 使用深度优先搜索在无向图的联通分量
 * 思想：对于图中每一个顶点，如果该顶点还没有被标记，就从该顶点出发进行深度优先搜索，找到并标记该顶点可达的所有顶点，并将这部分顶点归为一类。
 */

#include <iostream>
#include <vector>
#include "../../DataStruct/Graph/Graph.h"

using namespace std;

class ConnectedComponent {
public:
    ConnectedComponent(Graph &G);
    void dfs(Graph &G, int v);    // 深度优先
    bool connected(int v, int w); // 判断v和w是否连通
    int id(int v);                // 返回顶点v所在的连通分量
    int count();                  // 连通分量的个数

private:
    vector<int> marked_; // 标记访问过的节点
    vector<int> id_;     // 连通分量的id
    int count_;          // 连通分量数
};

ConnectedComponent::ConnectedComponent(Graph &G){
    marked_.assign(G.V(), false);
    id_.assign(G.V(), 0);
    count_ = 0;
    for (int v = 0; v < G.V(); v++){
        if (!marked_[v]) {
            dfs(G, v);
            count_++;
        }
    }
}

void ConnectedComponent::dfs(Graph &G, int v){
    marked_[v] = true;
    id_[v] = count_;
    for (int w: G.adj(v)){
        if (!marked_[w]){
            dfs(G, w);
        }
    }
}

bool ConnectedComponent::connected(int v, int w){
    return id_[v] == id_[w];
}

int ConnectedComponent::id(int v){
    return id_[v];
}

int ConnectedComponent::count(){
    return count_;
}

void testConnectedComponent(){
    int numberOfV = 8;
    Graph G(numberOfV);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 5);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(2, 4);
    G.addEdge(3, 4);
    G.addEdge(3, 5);
    G.addEdge(6, 7);
    G.output();
    ConnectedComponent cc(G);
    for (int v = 0; v < numberOfV; v++){
        cout << v << " : " << cc.id(v) << endl;
    }
}

int main(){
    testConnectedComponent();
    return 0;
}