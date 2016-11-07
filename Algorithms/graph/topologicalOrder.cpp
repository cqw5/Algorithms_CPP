/*! Author：qwchen
 *! Date  : 2016-10-18
 * 有向图的拓扑排序
 * 当一个有向图不存在环路时，有向图存在拓扑排序：否则，不存在拓扑排序
 * 思路：使用贪心方法，从左到右分布构造拓扑排列。每一步选择一个新的顶点加入序列中。
 *       选择新顶点时依据贪心准则：从剩余的顶点中选择一个顶点w，这个顶点w要么没有入边，如果存在入边，那么入边的发源结点必须已经在拓扑序列中。
 * 方法：用一个一维数组表示拓扑序列theOrder
 *       用一个栈来保存可加入theOrder的候选顶点
 *       用一个一维数组inDegree，其中inDegree[j]表示不在theOrder中但邻接至顶点j的顶点的数目。当inDegree[j]变为0时，表示顶点j成为一个候选顶点。
 *       初始时，序列theOrder为空，inDegree[j]就是顶点j的入度；每次向序列theOrder加入一个顶点时，所有邻接于该顶点的顶点j，inDegree[j]-1
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 图的数据结构
class Graph {
public:
    Graph(int num_v);
    ~Graph();
    void addEdge(int v, int w); // 添加边
    int V();                    // 返回图的结点数
    vector<int> adj(int v);     // 返回结点v的邻接数组
private:
    int num_v_;        // 图的结点数
    vector<int> *adj_; // 图的邻接数组
};

Graph::Graph(int num_v) {
    num_v_ = num_v;
    adj_ = new vector<int>[num_v];
}

Graph::~Graph(){
    delete []adj_;
}

void Graph::addEdge(int v, int w) {
    adj_[v].push_back(w);
}

int Graph::V() {
    return num_v_;
}

vector<int> Graph::adj(int v) {
    return adj_[v];
}

/*
 * Parament:
 *     G: 图
 *     theOrder: 图G的拓扑序列
 * Return：
 *     bool：若存在拓扑序列，返回true；若不存在(即存在有向环)，返回false
 *     theOrder：图的拓扑序列
 */
bool topologicalOrder(Graph G, vector<int> &theOrder){
    stack<int> candidate_vectex; // 存放所有候选结点栈
    int n = G.V();               // 图的结点数
    vector<int> inDegree(n, 0);  // inDegree[j]表示不在theOrder中但邻接至顶点j的顶点的数目
    // 计算每个结点的入度
    for(int v = 0; v < n; v++){
        for(auto w: G.adj(v)){
        inDegree[w]++;
        }
    }
    // 入度为0的结点接入候选栈
    for (int v = 0; v < n; v++) {
        if (0 == inDegree[v]) {
            candidate_vectex.push(v);
        }
    }
    // 每次向序列theOrder加入一个顶点时，所有邻接于该顶点的顶点j，inDegree[j]-1
    // 当inDegree[j]变为0时，表示顶点j成为一个候选顶点
    while(!candidate_vectex.empty()){
        int nextVectex = candidate_vectex.top();
        candidate_vectex.pop();
        theOrder.push_back(nextVectex);
        for (auto w: G.adj(nextVectex)) {
            inDegree[w]--;
            if (0 == inDegree[w]) {
                candidate_vectex.push(w);
            }
        }
    }
    if (theOrder.size() == n) return true;
    else return false;
}

void testTopologicalOrder() {
    Graph G(6);
    G.addEdge(0, 2);
    G.addEdge(0, 3);
    G.addEdge(2, 3);
    G.addEdge(1, 3);
    G.addEdge(1, 4);
    G.addEdge(2, 5);
    G.addEdge(3, 5);
    G.addEdge(4, 5);
    
    vector<int> theOrder;
    if (topologicalOrder(G, theOrder)){
        cout << "[Success], topologicalOrder is : ";
        for (int v: theOrder){
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "[Failed], Graph have cycle!" << endl;
    }
}

int main(){
    testTopologicalOrder();
    return 0;
}