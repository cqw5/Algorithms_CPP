/*! Author：qwchen
 *! Date  : 2016-11-6
 * 使用深度优先搜索有向图中是否存在环
 * 注意到有向图的存在环与无向图中存在环不同，如下面的图，当其为有向图时其无环；当其为无向图时其有环。
 *         0->1; 0->2; 1->3; 2->3
 * 思想：保存一个深度优先的当前栈（其实是一个数组），如果找到下一个结点为已标记并且在当前栈中，则存在环
 */

#include <iostream>
#include <vector>
#include <stack>
#include "../../DataStruct/Graph/Digraph.h"

using namespace std;

class DirectedCycle{
public:
    DirectedCycle(Digraph &G);
    void dfs(Digraph &G, int v);  // 深度优先
    bool hashCycle() const;       // 是否存在环
    vector<int> cycle();          // 返回环

private:
    vector<bool> marked_;   // 标记访问过的顶点
    vector<int> edgeTo_;    // 保存当前顶点的前一个顶点
    stack<int> cycle_;      // 保存有向环
    vector<bool> onStack_;  // 用一个数组来表示深度优先递归的当前栈，之所以不直接用stack的数据结构来表示，是因为stack没法判断元素是在栈中。
                            // 而用数组很容易判断
};

DirectedCycle::DirectedCycle(Digraph &G){
    marked_.assign(G.V(), false);
    edgeTo_.assign(G.V(), 0);
    onStack_.assign(G.V(), false);
    for (int v = 0; v < G.V(); v++){
        if (!marked_[v]){
            dfs(G, v);
        }
    }
}

void DirectedCycle::dfs(Digraph &G, int v){
    onStack_[v] = true;
    marked_[v] = true;
    for (int w: G.adj(v)){
        if (hashCycle()) return;  // 找到一个环就可以说明存在环了
        else if (!marked_[w]){
            edgeTo_[w] = v;
            dfs(G, w);
        } else if (onStack_[w]){
            // 存在环了，把环保存在栈中
            for(int x = v; x != w; x = edgeTo_[x]){
                cycle_.push(x);
            }
            cycle_.push(w);
            cycle_.push(v); // 首尾push两次v，看起来输出时看起开就像环
        }
    }
    onStack_[v] = false;
}

bool DirectedCycle::hashCycle() const {
    return !cycle_.empty();
}

vector<int> DirectedCycle::cycle(){
    vector<int> theCycle;
    while(!cycle_.empty()){
        theCycle.push_back(cycle_.top());
        cycle_.pop();
    }
    return theCycle;
}

void testDirectedCycle(){
    Digraph G1(4);
    G1.addEdge(0, 1);
    G1.addEdge(1, 2);
    G1.addEdge(2, 3);
    G1.addEdge(3, 1);
    DirectedCycle cycle1(G1);
    if(cycle1.hashCycle()){
        cout << "Graph1 has cycle: ";
        for (int v: cycle1.cycle()){
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "Graph1 has not cycle." << endl;
    }

    Digraph G2(4);
    G2.addEdge(0, 1);
    G2.addEdge(0, 2);
    G2.addEdge(1, 3);
    G2.addEdge(2, 3);
    DirectedCycle cycle2(G2);
    if(cycle2.hashCycle()){
        cout << "Graph2 has cycle: ";
        for (int v: cycle2.cycle()){
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "Graph2 has not cycle." << endl;
    }
}

int main(){
    testDirectedCycle();
    return 0;
}