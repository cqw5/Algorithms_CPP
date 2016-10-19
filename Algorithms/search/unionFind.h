/*!
 * 查并集(基于树实现)
 * 思路：将一个集合表示为一个森林，其中每一个等价类是一棵树
 *       使用union(class1, class2)将两个等价类合并为一个等价类，只需要让一棵树成为另一棵树的子树。
 *       使用find(element)来查找元素element所在的集合标志符
 */

#ifndef unionFind_
#define unionFind_

#include <iostream>
#include <vector>

using namespace std;

struct unionFindNode {
    int parent;         // 结点的父节点指针
    bool is_root;       // 结点是否是根结点，是为true
    unionFindNode(){
        parent = -1;    // 另根结点的父节点为-1，即不存在
        is_root = true;
    }
};

class unionFind {
public:
    unionFind(int num_node);            // 构造函数，num_node为集合中结点的个数
    int find(int element) const;        // 查找结点element的集合id，返回集合id
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


