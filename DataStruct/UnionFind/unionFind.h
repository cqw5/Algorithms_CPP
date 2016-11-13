 /*! Author: qwchen
  *! Date  : 2016-11-13
  * 查并集(基于树实现)
  * 思路：使用森林来表示并查集，其中每一棵树是一个集合；树的每个节点就表示集合中的一个元素，树根对应的元素就是该集合的代表。
  *       使用union(class1, class2)将两个等价类合并为一个等价类，只需要让一棵树成为另一棵树的子树。
  *       使用find(element)来查找元素element所在的集合标志符
  */

#ifndef unionFind_
#define unionFind_

#include <iostream>
#include <vector>

using namespace std;

struct unionFindNode {
    int parent;         // 节点的父节点指针
    bool is_root;       // 节点是否是根节点，是为true
    unionFindNode(){
        parent = -1;    // 另根节点的父节点为-1，即不存在
        is_root = true; // 初始化时每个集合中都只有一个节点，因此每个节点都为根节点
    }
};

class unionFind {
public:
    unionFind(int num_node);            // 构造函数，num_node为集合中节点的个数
    int find(int element) const;        // 查找节点element的集合id，返回集合id
    void unite(int class1, int class2); // 将两个集合id所代表的集合合并
private:
    vector<unionFindNode> node;
};

unionFind::unionFind(int num_node){
    vector<unionFindNode> tmp_node(num_node);
    node = tmp_node;
}

int unionFind::find(int element) const{
    while(!node[element].is_root) {
        element = node[element].parent;
    }
    return element;
}

void unionFind::unite(int class1, int class2){
    node[class1].parent = class2;
    node[class1].is_root = false;
}

#endif


