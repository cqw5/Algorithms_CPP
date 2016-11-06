/*! Author：qwchen
 *! Date  : 2016-11-6
 * 使用深度优先搜索无向图中是否存在环
 * 思想：对图进行深度优先搜索，如果当前顶点相邻的顶点已经被标记，并且该被标记的顶点不是当前顶点的上一个顶点，则存在环。
 *       进行深度优先搜索时，保存上一个顶点。
 */

#include <iostream>
#include <vector>
#include "../../DataStruct/Graph/Graph.h"

using namespace std;

class Cycle{
public:
    Cycle(Graph &G);
    void dfs(Graph &G, int v, int u); // u是v的上一个顶点
    bool hasCycle();                  // 返回true当图存在环时

private:
    vector<bool> marked_;  // 标记访问过的节点
    bool hasCycle_;        // 标记图是否存在环
};

Cycle::Cycle(Graph &G){
    marked_.assign(G.V(), false);
    hasCycle_ = false;
    for(int v = 0; v < G.V(); v++){
        if (!marked_[v]){
            dfs(G, v, v);
            if (hasCycle_) break;
        }
    }
}

void Cycle::dfs(Graph &G, int v, int u){
    marked_[v] = true;
    for (int w: G.adj(v)){
        if (!marked_[w]){
            dfs(G, w, v);
        } else {
            if (w != u){ // 如果当前顶点相邻的顶点已经被标记，并且该被标记的顶点不是当前顶点的上一个顶点，则肯定存在环
                hasCycle_ = true;
                return;
            }
        }
    }
}

bool Cycle::hasCycle(){
    return hasCycle_;
}

void testCycle(){
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
    Cycle cycle(G);
    if (cycle.hasCycle()){
        cout << "Graph has cycle!" << endl;
    } else {
        cout << "Graph hasn't cycle!" << endl;
    }
}

int main(){
    testCycle();
    return 0;
}
