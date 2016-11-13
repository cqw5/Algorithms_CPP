 /*! Author: qwchen
  *! Date  : 2016-11-13
  * 基于 路径压缩 + 重量规则 优化的并查集
  */

#ifndef optimizeUnionFind_
#define optimizeUnionFind_

#include <iostream>
#include <vector>

using namespace std;

struct unionFindNode {
    int parent;         // 若为真，则表示树的重量，否则是指向父节点的指针
    bool is_root;       // 节点是否是根节点，是为true
    unionFindNode(){
        parent = 1;     // 初始化时每个集合中都只有一个节点，此时parent表示树的重量
        is_root = true; // 初始化时每个集合中都只有一个节点，因此每个节点都为根节点
    }
};

class optimizeUnionFind {
public:
    optimizeUnionFind(int num_node);    // 构造函数，num_node为集合中节点的个数
    int find(int element);              // 查找节点element的集合id，返回集合id
    void unite(int class1, int class2); // 将两个集合id所代表的集合合并
private:
    vector<unionFindNode> node;
};

optimizeUnionFind::optimizeUnionFind(int num_node){
    vector<unionFindNode> tmp_node(num_node);
    node = tmp_node;
}

// 返回元素element所在树的根，压缩从元素element到根的路径
int optimizeUnionFind::find(int element){
    // root最终是树的根节点
    int root = element;
    while(!node[root].is_root){
        root = node[root].parent;
    }
    // 压缩从element到root的路径
    int currentNode = element;  // 从element开始压缩
    while(currentNode != root){
        int parentNode = node[currentNode].parent;
        node[currentNode].parent = root;
        currentNode = parentNode;
    }
    return root;
}

// 使用重量规则，合并根节点不同的两棵树（class1 和 class2）
void optimizeUnionFind::unite(int class1, int class2){
    if (node[class1].parent <= node[class2].parent){ // 树class1成为树class2的子树
        node[class2].parent += node[class1].parent;
        node[class1].is_root = false;
        node[class1].parent = class2;
    } 
    else { // 树class2成为class1的子树
        node[class1].parent += node[class2].parent;
        node[class2].is_root = false;
        node[class2].parent = class1;
    }
}

#endif