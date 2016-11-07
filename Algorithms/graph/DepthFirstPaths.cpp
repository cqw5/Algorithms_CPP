/*! Author：qwchen
 *! Date  : 2016-11-6
 * 使用深度优先搜索在无向图中寻找路径
 * 思想：使用深度优先搜索从图的顶点s出发，能被访问到的节点都是可达的节点；用edgeTo[v]表示从s出发到v的路径上的最后一个顶点，
 *       只要通过edgeTo回溯，就可以找到从s到v的路径。
 */

#include <iostream>
#include <vector>
#include <stack>
#include "../../DataStruct/Graph/Graph.h"

using namespace std;

class DepthFirstPaths{
public:
    DepthFirstPaths(Graph &G, int s);
    void dfs(Graph &G, int v);  // 深度优先搜索
    bool hashPathTo(int v);     // 返回true，当存在从s到v的可达路径
    vector<int> pathTo(int v);  // 返回从s到v的可达路径

private:
    vector<bool> marked_; // 标记访问过的节点
    vector<int> edgeTo_;  // 从起点s到一个顶点的已知路径上的最后一个顶点
    int s_;               // 起点
};

DepthFirstPaths::DepthFirstPaths(Graph &G, int s){
    marked_.assign(G.V(), false);
    edgeTo_.assign(G.V(), 0);
    s_ = s;
    dfs(G, s);
}

void DepthFirstPaths::dfs(Graph &G, int v){
    marked_[v] = true;
    for (int w: G.adj(v)){
        if (!marked_[w]){
            edgeTo_[w] = v;
            dfs(G, w);
        }
    }
}

bool DepthFirstPaths::hashPathTo(int v){
    return marked_[v];
}

vector<int> DepthFirstPaths::pathTo(int v){
    // 通过stack反向存储路径，出栈就是正向路径
    vector<int> path;
    stack<int> pathReverse;
    for (int t = v; t != s_; t = edgeTo_[t]){
        pathReverse.push(t);
    }
    pathReverse.push(s_);
    while(!pathReverse.empty()){
        path.push_back(pathReverse.top());
        pathReverse.pop();
    }
    return path;
}

void testDepthFirstPaths(){
    int numberOfV = 6;
    Graph G(numberOfV);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 5);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(2, 4);
    G.addEdge(3, 4);
    G.addEdge(3, 5);
    G.output();
    DepthFirstPaths dfp(G, 0);
    for (int v = 1; v < numberOfV; v++){
        cout << "Path from 0 to " << v << " : ";
        if (dfp.hashPathTo(v)){
            for (int t: dfp.pathTo(v)){
                cout << t << " ";
            }
            cout << endl;
        } else {
            cout << "Have not path from 0 to " << v << endl;
        }
    }
}

int main(){
    testDepthFirstPaths();
    return 0;
}