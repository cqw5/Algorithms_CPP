/*! Author：qwchen
 *! Date  : 2016-11-7
 * 有向图深度优先的顶点排序
 * 前序：在递归调用之前将顶点加入队列
 * 后序：在递归调用之后将顶点加入队列
 * 逆后序：在递归调用之后将顶点压入栈
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "../../DataStruct/Graph/Digraph.h"

using namespace std;

class DepthFirstOrder {
public:
    DepthFirstOrder(Digraph& G);
    void dfs(Digraph& G, int v);
    queue<int> pre();
    queue<int> post();
    stack<int> reversePost();

private:
    vector<bool> marked_;
    queue<int> pre_;
    queue<int> post_;
    stack<int> reversePost_;
};

DepthFirstOrder::DepthFirstOrder(Digraph& G){
    marked_.assign(G.V(), false);
    for (int v = 0; v < G.V(); v++){
        if (!marked_[v]) dfs(G, v);
    }
}

void DepthFirstOrder::dfs(Digraph& G, int v){
    marked_[v] = true;
    pre_.push(v);
    for (int w: G.adj(v)){
        if (!marked_[w]){
            dfs(G, w);
        }
    }
    post_.push(v);
    reversePost_.push(v);
}

queue<int> DepthFirstOrder::pre(){
    return pre_;
}

queue<int> DepthFirstOrder::post(){
    return post_;
}

stack<int> DepthFirstOrder::reversePost(){
    return reversePost_;
}

void testDepthFirstOrder(){
    int numberOfV = 13;
    Digraph G(numberOfV);
    G.addEdge(0, 1);
    G.addEdge(0, 5);
    G.addEdge(0, 6);
    G.addEdge(2, 0);
    G.addEdge(2, 3);
    G.addEdge(3, 5);
    G.addEdge(5, 4);
    G.addEdge(6, 4);
    G.addEdge(7, 6);
    G.addEdge(8, 7);
    G.addEdge(6, 9);
    G.addEdge(9, 10);
    G.addEdge(9, 11);
    G.addEdge(9, 12);
    G.addEdge(11, 12);
    G.output();
    DepthFirstOrder dfo(G);
    queue<int> pre = dfo.pre();
    queue<int> post = dfo.post();
    stack<int> reversePost = dfo.reversePost();
    cout << "PreOrder: ";
    while(!pre.empty()){
        cout << pre.front() << " ";
        pre.pop();
    }
    cout << endl;
    cout << "PostOrder: ";
    while(!post.empty()){
        cout << post.front() << " ";
        post.pop();
    }
    cout << endl;
    cout << "ReversePostOrder: ";
    while(!reversePost.empty()){
        cout << reversePost.top() << " ";
        reversePost.pop();
    }
    cout << endl;
}

int main(){
    testDepthFirstOrder();
    return 0;
}