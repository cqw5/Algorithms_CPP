/*！Author: qwchen
 *! Date: 2016-10-27
 * 加权有向图(可以有负权重边，但不能有负权重环)的最短路径：Bellman-Ford算法
 * 思想：构造edgeTo[v](s到v的最短路径上的最后一条边) 和 distTo[v](s到v的已知的最短路径的长度)，
 *       之后判断是否有最短路径、最短路径长度、最短路径，都可以从edgeTo[]和distTo[]得出
 * 方法：将s放入到队列中，然后不断放松队头的顶点并出队列；(队列是用来保存上一轮中distTo[]值发生改变的顶点，
 *       因为由这些顶点指出的边才能改变其他distTo[]元素的值)
 *       每放松一个结点v时，检查从该结点指出的有向边e所指向的结点w的 distTo[w] > distTo[v] + e.weight:
 *           若是，修改distTo[w]和edgeTo[w]
 *               若该结点w不在队列中，将w放入队列中；若已经在队列中，则不用重复放入
 *           若不是，不进行操作
 *       直到队列为空时，结束
 * Bellman-Ford算法是一种动态规划算法，一般情况下时间复杂度O(E+V)，最坏情况下时间复杂度是O(VE)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <float.h>
#include "../../DataStruct/Graph/EdgeWeightedDigraph.h"

using namespace std;

// Bellman-Ford算法寻找最短路径
class BellmanFordShortPath {
public:
    BellmanFordShortPath(EdgeWeightedDigraph &G, int s);
    double distTo(int v);              // 从顶点s到v的距离
    bool hasPathTo(int v);             // 是否存在从顶点s到v的路径
    stack<DirectedEdge> pathTo(int v); // 从顶点s到v的路径
private:
    void relax(EdgeWeightedDigraph &G, int v); // 放松结点v
    vector<DirectedEdge> edgeTo_;              // edgeTo[v]的值为s到v的最短路径上的最后一条边
    vector<double> distTo_;                    // distTo[v]的值为s到v的已知的最短路径的长度
    queue<int> queue_;                         // 队列保存候选的待放松的结点
    vector<bool> onQ_;                         // 记录结点是否在队列中
    int s_;                                    // 起始结点
};

BellmanFordShortPath::BellmanFordShortPath(EdgeWeightedDigraph &G, int s){
    s_ = s;
    int n = G.V();
    // 初始化edgeTo[]
    vector<DirectedEdge> tmp_edgeTo(n);
    edgeTo_ = tmp_edgeTo;
    // 初始化distTo[]，n个，第一个为0，其他为DBL_MAX
    vector<double> tmp_distTo(n, DBL_MAX);
    tmp_distTo[0] = 0.0;
    distTo_ = tmp_distTo;
    // 初始化onQ[]，n个，第一个位true，其他为false
    vector<bool> tmp_onQ(n, false);
    tmp_onQ[0] = true;
    onQ_ = tmp_onQ;
    // 将原点放入队列
    queue_.push(s);
    while (!queue_.empty()) {
        // 放松队头元素
        int v = queue_.front();
        queue_.pop();
        onQ_[v] = false;
        relax(G, v);
    }
}

void BellmanFordShortPath::relax(EdgeWeightedDigraph &G, int v){
    for (DirectedEdge e: G.adj(v)) {
        int w = e.to();
        if (distTo_[w] > distTo_[v] + e.weight()){
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo_[w] = e;
            if (!onQ_[w]){
                queue_.push(w);
                onQ_[w] = true;
            }
        }
    }
}

double BellmanFordShortPath::distTo(int v) {
    return distTo_[v];
}

bool BellmanFordShortPath::hasPathTo(int v) {
    return distTo_[v] != DBL_MAX;
}

stack<DirectedEdge> BellmanFordShortPath::pathTo(int v) {
    stack<DirectedEdge> path;
    DirectedEdge e = edgeTo_[v];
    for (; e.from() != s_; e = edgeTo_[e.from()]) {
        path.push(e);
    }
    path.push(e);
    return path;
}


void testBellmanFordShortPath() {
    EdgeWeightedDigraph G(8);
    G.addEdge(4, 5, 0.35);
    G.addEdge(5, 4, 0.35);
    G.addEdge(4, 7, 0.37);
    G.addEdge(5, 7, 0.28);
    G.addEdge(7, 5, 0.28);
    G.addEdge(5, 1, 0.32);
    G.addEdge(0, 4, 0.38);
    G.addEdge(0, 2, 0.26);
    G.addEdge(7, 3, 0.39);
    G.addEdge(1, 3, 0.29);
    G.addEdge(2, 7, 0.34);
    G.addEdge(6, 2, -1.20);
    G.addEdge(3, 6, 0.52);
    G.addEdge(6, 0, -1.40);
    G.addEdge(6, 4, -1.25);
    for (int i = 0; i < G.V(); i++){
        cout << i;
        for (DirectedEdge e: G.adj(i)) {
            int v = e.from();
            int w = e.to();
            double weight = e.weight();
            cout << "(" << v << " -> " << w << " : " << weight << " )";
        }
        cout << endl;
    }
    
    BellmanFordShortPath SP(G, 0);
    if (SP.hasPathTo(6)){
        cout << "0 has path to 6" << endl;
        cout << "Dist from 0 to 6 : " <<SP.distTo(6) << endl;
    } else {
        cout << "0 no path to 6" << endl;
    }
    cout << "Path from 0 to 6 : ";
    stack<DirectedEdge> stack_edge = SP.pathTo(6);
    while(!stack_edge.empty()) {
        DirectedEdge e = stack_edge.top();
        stack_edge.pop();
        cout << e.from() << " ";
    }
    cout << "6" << endl;
}

int main(){
    testBellmanFordShortPath();
    return 0;
}
