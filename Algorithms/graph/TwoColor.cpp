/*! Author：qwchen
 *! Date  : 2016-11-6
 * 使用深度优先搜索无向图中是否为二分图
 * 思想：对图进行深度优先搜索，如果当前顶点相邻的顶点已经被被染色，并且颜色与当前顶点相同，则图不是二分图
 */

#include <iostream>
#include <vector>
#include "../../DataStruct/Graph/Graph.h"

using namespace std;

class TwoColor{
public:
	TwoColor(Graph &G);
	void dfs(Graph &G, int v);
	bool isBipartite();

private:
	vector<bool> marked_;
	vector<bool> color_;
	bool isTwoColorable_;
};

TwoColor::TwoColor(Graph &G){
	marked_.assign(G.V(), false);
	color_.assign(G.V(), false);
	isTwoColorable_ = true;
	for (int v = 0; v < G.V(); v++){
		if (!marked_[v]){
			dfs(G, v);
		}
	}
}

void TwoColor::dfs(Graph &G, int v){
	marked_[v] = true;
	for(int w: G.adj(v)){
		if(!marked_[w]){
			color_[w] = !color_[v];
			dfs(G, w);
		} else {
			if (color_[w] == color_[v]){
				isTwoColorable_ = false;
				return;
			}
		}
	}
}

bool TwoColor::isBipartite(){
	return isTwoColorable_;
}

void testTwoColor(){
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
    TwoColor tc(G);
    if (tc.isBipartite()){
    	cout << "Graph is two color." << endl;
    } else {
    	cout << "Graph is not two color." << endl;
    }
}

int main(){
	testTwoColor();
	return 0;
}

