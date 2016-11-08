/*！Author: qwchen
 *! Date: 2016-11-8
 * 加权有向图(权重非负)的最短路径：Dijkstra算法
 * 思想：构造edgeTo[v](s到v的最短路径上的最后一条边) 和 distTo[v](s到v的已知的最短路径的长度)，
 *       之后判断是否有最短路径、最短路径长度、最短路径，都可以从edgeTo[]和distTo[]得出
 * 方法：将s放入到小顶堆中，然后不断放松小顶堆中最小的结点；
 *       每放松一个结点v时，检查从该结点指出的有向边e所指向的结点w的 distTo[w] > distTo[v] + e.weight:
 *           若是，修改distTo[w]和edgeTo[w]，并将w放入堆中
 *           若不是，不进行操作
 *       直到小顶堆为空时，结束
 * Dijkstra是一种贪心算法，一般情况下时间复杂度O(ElogV)，最坏情况下时间复杂度也是O(ElogV)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <float.h>
#include <stack>
#include "../../DataStruct/Graph/EdgeWeightedDigraph.h"

using namespace std;

// 定义最小堆中存储的的结点
class vectexInHeap {
public:
    vectexInHeap() {}
    vectexInHeap(int v, double distTo) { v_ = v; distTo_ = distTo; }
    int v() const { return v_; }
    double distTo() const { return distTo_; }
    void setDistTo(double distTo) { distTo_ = distTo; }
    operator double() const { return distTo_; }
private:
    int v_;           // 结点
    double distTo_;   // 结点到起始结点的距离
};

// Dijstra算法寻找最短路径
class DijstraShortPath {
// 调bug启示，第一次写时，DijstraShortPath和relax函数的EdgeWeightedDigraph &G没有加上应用，一直出错。
public:
    DijstraShortPath(EdgeWeightedDigraph &G, int s);
    double distTo(int v);              // 从顶点s到v的距离
    bool hasPathTo(int v);             // 是否存在从顶点s到v的路径
    stack<DirectedEdge> pathTo(int v);   // 从顶点s到v的路径
private:
    void relax(EdgeWeightedDigraph &G, int v);  // 放松结点v
    vector<DirectedEdge> edgeTo_;                // edgeTo[v]的值为s到v的最短路径上的最后一条边
    vector<double> distTo_;                    // distTo[v]的值为s到v的已知的最短路径的长度
    vector<vectexInHeap> minheap_;             // 小顶堆保存候选的待放松的结点
    int s_;                                    // 起始结点
};

/*
 * 自定义比较堆中元素大小的函数
 */ 
bool greater_vectex(const vectexInHeap &v1, const vectexInHeap &v2) {
    return v1 > v2;
}

/*
 * Dijstra算法，目标是生成edgeTo数组和distTo数组
 * parament:
 *     G: 加权有向图
 *     s：起始顶点
 */
DijstraShortPath::DijstraShortPath(EdgeWeightedDigraph &G, int s) {
    s_ = s;
    int n = G.V();
    // 初始化edgeTo
    vector<DirectedEdge> tmp_edgeTo(n);
    edgeTo_ = tmp_edgeTo;
    // 初始化distTo
    vector<double> tmp_distTo(n, DBL_MAX);
    tmp_distTo[0] = 0.0;
    distTo_ = tmp_distTo;
    // 创建小顶堆
    make_heap(minheap_.begin(), minheap_.end(), greater_vectex);
    // 将结点s放入小顶堆中
    minheap_.push_back(vectexInHeap(s, 0.0)); push_heap(minheap_.begin(), minheap_.end(), greater_vectex);
    while (!minheap_.empty()) {  // 小顶堆不为空执行循环
        // 取出小顶堆堆顶的结点，进行放松
        int vertex = minheap_.front().v();
        pop_heap(minheap_.begin(), minheap_.end(), greater_vectex); minheap_.pop_back();
        relax(G, vertex);
    }
}

/*
 * 放松顶点
 * Parament：
 *     G：加权有向图
 *     v：待发送的顶点
 */
void DijstraShortPath::relax(EdgeWeightedDigraph &G, int v) {
    for (DirectedEdge e : G.adj(v)) {
        int w = e.to();  // 从放松的结点指出的有向边指向的结点
        if (distTo_[w] > distTo_[v] + e.weight()) {
            double old_distTo_w = distTo_[w];
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo_[w] = e;
            auto exist_w = find(minheap_.begin(), minheap_.end(), vectexInHeap(w, old_distTo_w));
            if (exist_w == minheap_.end()) { // 结点w不在堆中，将w入堆
                minheap_.push_back(vectexInHeap(w, distTo_[w])); push_heap(minheap_.begin(), minheap_.end(), greater_vectex);
            }
            else { // 已经在堆中
                (*exist_w).setDistTo(distTo_[w]);
            }
        }
    }
}

double DijstraShortPath::distTo(int v) {
    return distTo_[v];
}

bool DijstraShortPath::hasPathTo(int v) {
    return distTo_[v] != DBL_MAX;
}

stack<DirectedEdge> DijstraShortPath::pathTo(int v) {
    stack<DirectedEdge> path;
    DirectedEdge e = edgeTo_[v];
    for (; e.from() != s_; e = edgeTo_[e.from()]) {
        path.push(e);
    }
    path.push(e);
    return path;
}

void testDijstraShortPath() {
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
    G.addEdge(6, 2, 0.40);
    G.addEdge(3, 6, 0.52);
    G.addEdge(6, 0, 0.58);
    G.addEdge(6, 4, 0.93);
    DijstraShortPath SP(G, 0);
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
    testDijstraShortPath();
    return 0;
}

