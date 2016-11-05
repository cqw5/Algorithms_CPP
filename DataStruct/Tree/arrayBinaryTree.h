/*! Author: qwchen
 *! Date: 2016-10-10
 * 基于数组实现的二叉树
 * 数组下标从1开始
 */

#ifndef arrayBinaryTree_
#define arrayBinaryTree_

#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class arrayBinaryTree {
public:
    arrayBinaryTree(int size, T *pRoot);                 // 接收数组长度和树的根结点元素，创建二叉树
    ~arrayBinaryTree();
    T searchNode(int theIndex);                        // 根据索引寻找结点
    void addNode(int theIndex, int direction, T *pNode); // 添加结点，theIndex是待插入结点的父结点，direction = 0代表左子树,direction = 1代表右子树
    void deleteNode(int theIndex, T *pNode);             // 删除结点，将被删除的结点放到pNode中返回
    void treeTrave();                                    // 遍历结点

private:
    T *m_pTree; // 数组
    int m_iSize;  // 数组元素的个数
};

template <class T>
arrayBinaryTree<T>::arrayBinaryTree(int size, T *pRoot) {
    m_pTree = new T[size + 1];
    m_iSize = size;
    for (int i = 0; i <= size; i++) {
        m_pTree[i] = 0;
    }
    m_pTree[1] = *pRoot;
}

template <class T>
arrayBinaryTree<T>::~arrayBinaryTree() {
    delete []m_pTree;
}

template <class T>
T arrayBinaryTree<T>::searchNode(int theIndex) {
    if (theIndex <= 0 || theIndex > m_iSize) {
        return 0;
    }
    return m_pTree[theIndex];
}

template <class T>
void arrayBinaryTree<T>::addNode(int theIndex, int direction, T *pNode) {
    if (theIndex <= 0 || theIndex > m_iSize) {
        stringstream s;
        s << "index out of range." << endl;
        throw invalid_argument(s.str());
    }
    if (m_pTree[theIndex] == 0) { // 父节点不存在，插入失败
        stringstream s;
        s << "parent node doesn't exist." << endl;
        throw invalid_argument(s.str());
    }
    // 寻找插入位置，是左孩子还是右孩子
    if (direction == 0) theIndex = 2 * theIndex;
    else if (direction == 1) theIndex = 2 * theIndex + 1;
    else {
        stringstream s;
        s << "direction must be 0 or 1" << endl;
        throw invalid_argument(s.str());
    }
    // 子节点越界，插入失败
    if (theIndex <= 0 || theIndex > m_iSize) {
        stringstream s;
        s << "index out of range." << endl;
        throw invalid_argument(s.str());
    }
    // 子节点已经存在，插入失败
    if (m_pTree[theIndex] != 0) {
        stringstream s;
        s << "node have already exist." << endl;
        throw invalid_argument(s.str());
    }
    m_pTree[theIndex] = *pNode;
}

template <class T>
void arrayBinaryTree<T>::deleteNode(int theIndex, T *pNode) {
    if (theIndex <= 0 || theIndex > m_iSize) {
        stringstream s;
        s << "direction must be 0 or 1" << endl;
        throw invalid_argument(s.str());
    }
    if (m_pTree[theIndex] == 0) {
        stringstream s;
        s << "node doesn't exist." << endl;
        throw invalid_argument(s.str());
    }
    *pNode = m_pTree[theIndex];
    m_pTree[theIndex] = 0;
}

template <class T>
void arrayBinaryTree<T>::treeTrave() {
    for (int i = 1; i <= m_iSize; i++) {
        cout << m_pTree[i] << " ";
    }
}

#endif // !arrayBinaryTree_





