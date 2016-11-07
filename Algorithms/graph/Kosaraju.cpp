/*! Author：qwchen
 *! Date  : 2016-11-6
 * 计算有向图无权图的强连通分量的Kosaraju算法
 * 思路：1.给定一幅图G，先计算它的反向图的逆后序排列
 *       2.在G中进行标准的深度优先搜索，但是按照刚才计算得到的顺序而非标准的顺序来访问所有为被标记的结点
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
public:
    Graph(int num_v);
    void addEdge(int v, int w);
    void dfs(int v, bool marked[]);         // 深度优先
    Graph getReverse();                     // 获取图的反向图
    void getReversePost(Graph &G, int v, bool marked[], stack<int> &reverse_post_stack); // 获取图的逆后序排列
    void printStronglyConnectedComponent(); // 输出图的强连通子图
private:
    int num_v_;        // 图的结点数
    vector<int> *adj_; // 图的邻接数组
};

Graph::Graph(int num_v) {
    num_v_ = num_v;
    adj_ = new vector<int>[num_v];
}

void Graph::addEdge(int v, int w) {
    adj_[v].push_back(w);
}

void Graph::dfs(int v, bool marked[]) {
    marked[v] = true;
    cout << v << " ";
    for (auto w = adj_[v].begin(); w != adj_[v].end(); ++w) {
        if (!marked[*w]) {
            dfs(*w, marked);
        }
    }
}

Graph Graph::getReverse() {
    Graph reverse_G(num_v_);
    for (int v = 0; v < num_v_; v++) {
        for (auto w = adj_[v].begin(); w != adj_[v].end(); ++w) {
            reverse_G.adj_[*w].push_back(v);
        }
    }
    return reverse_G;
}

void Graph::getReversePost(Graph &G, int v, bool marked[], stack<int> &reverse_post_stack) {
    marked[v] = true;
    for (auto w = G.adj_[v].begin(); w != G.adj_[v].end(); ++w) {
        if (!marked[*w]) {
            getReversePost(G, *w, marked, reverse_post_stack);
        }
    }
    reverse_post_stack.push(v); // 逆后序：在递归调用之后将顶点压入栈
}

void Graph::printStronglyConnectedComponent() {
    // marked用来标记已访问过的结点，初始值为false，访问过为true
    bool *marked = new bool[num_v_];
    for (int i = 0; i < num_v_; i++) {
        marked[i] = false;
    }
    // 获取图G的反向图reverse_G
    Graph reverse_G = getReverse();
    // 后续出栈的顺序就是逆后序遍历的顺序
    stack<int> reverse_post_stack;
    for (int v = 0; v < num_v_; ++v) {
        if (!marked[v]) {
            getReversePost(reverse_G, v, marked, reverse_post_stack);
        }
    }
    for (int i = 0; i < num_v_; i++) {
    	marked[i] = false;
    }
    // 按照反向图reverse_G的逆后序遍历的顺序对图G进行DFS
    while (!reverse_post_stack.empty()) {
        int v = reverse_post_stack.top();
        reverse_post_stack.pop();
        if (!marked[v]) {
            dfs(v, marked);
            cout << endl;
        }
    }
}

// 测试
void testKosaraju() {
    Graph G(5);
    G.addEdge(1, 0);
    G.addEdge(0, 2);
    G.addEdge(2, 1);
    G.addEdge(0, 3);
    G.addEdge(3, 4);
    cout << "The strongly connected components in given graph" << endl;
    G.printStronglyConnectedComponent();
}

int main(){
    testKosaraju();
    return 0;
}