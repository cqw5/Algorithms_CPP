/*! Author: qwchen
 *! Date: 2016-10-10
 * 基于链表实现的二叉树
 */

#ifndef linkedBinaryTree_
#define linkedBinaryTree_

#include <iostream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

/*
 * 二叉树结点
 */
template <class T>
struct binaryTreeNode {
    T element;                      // 结点元素
    binaryTreeNode<T> *leftChild;   // 左子树
    binaryTreeNode<T> *rightChild;  // 右子树
    
    binaryTreeNode() {
        leftChild = rightChild = NULL;
    }

    binaryTreeNode(const T& theElement):element(theElement) {
        leftChild = rightChild = NULL;
    }

    binaryTreeNode(const T& theElement, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild) :element(theElement) {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

/*
 * 链表实现的二叉树
 */
template <class T>
class linkedBinaryTree {
public:
    linkedBinaryTree() { // 创建二叉树
        root = NULL;
        treeSize = 0;
    }
    ~linkedBinaryTree() { // 销毁二叉树
        visit = dispose;
        postOrder(root);
        root = NULL;
    }
    bool empty() const {  // 判断树是否为空
        return treeSize == 0;
    }
    int size() const {    // 返回树的结点数
        return treeSize;
    }
    T* rootElement() const {  //返回树的根结点的值
        if (empty()) return NULL;
        else return &root->element;
    }
    void makeTree(const T& element, linkedBinaryTree<T>&, linkedBinaryTree<T>&); // 给定根结点、左子树和右子树，创建一块新的树
    linkedBinaryTree<T>& removeLeftSubtree();  // 删除并返回左子树
    linkedBinaryTree<T>& removeRightSubtree(); // 删除并返回右子树
    void preOrder() {    // 先序遍历
        visit = output;
        preOrder(root);
        cout << endl;
    }
    void inOrder() {    // 中序遍历
        visit = output;
        inOrder(root);
        cout << endl;
    }
    void postOrder() {  // 后续遍历
        visit = output;
        postOrder(root);
        cout << endl;
    }
    void levelOrder() { // 层次遍历
        visit = output;
        levelOrder(root);
        cout << endl;
    }
    int height() {      // 树的高度
        return height(root);
    }
    void preOrderUnRecursive() { // 先序遍历（非递归版本）
        visit = output;
        preOrderUnRecursive(root);
        cout << endl;
    }
    void inOrderUnRecursive() {  // 中序遍历（非递归版本）
        visit = output;
        inOrderUnRecursive(root);
        cout << endl;
    }
    void postOrderUnRecursive() {// 后序遍历（非递归版本）
        visit = output;
        postOrderUnRecursive(root);
        cout << endl;
    }

protected:
    binaryTreeNode<T> *root;                      // 二叉树
    int treeSize;                                 // 二叉树结点数
    static int count;                             // 用于子树结点数计数
    static void(*visit)(binaryTreeNode<T> *t);    // visit函数，一个指针函数，可以根据功能指向不同的函数
    static void preOrder(binaryTreeNode<T> *t);   // 先序遍历
    static void inOrder(binaryTreeNode<T> *t);    // 中序遍历
    static void postOrder(binaryTreeNode<T> *t);  // 后续遍历
    static void levelOrder(binaryTreeNode<T> *t); // 层次遍历
    static void preOrderUnRecursive(binaryTreeNode<T> *t);  // 先序遍历（非递归版本）
    static void inOrderUnRecursive(binaryTreeNode<T> *t);   // 中序遍历（非递归版本）
    static void postOrderUnRecursive(binaryTreeNode<T> *t); // 后序遍历（非递归版本）
    static int height(binaryTreeNode<T> *t);                // 树的高度
    static void output(binaryTreeNode<T> *t) { cout << t->element << " "; } // visit可以指向的功能函数，输出当前结点的值
    static void addToCount(binaryTreeNode<T> *t) { count++; }  // visit可以指向的功能函数，计数
    static void dispose(binaryTreeNode<T> *t) { delete t; }    // visit可以指向的功能函数，删除结点
    static int countNode(binaryTreeNode<T> *t) {
        count = 0;
        visit = addToCount;
        preOrder(t);
        return count;
    }
};

template <class T> 
void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T>*);

template <class T>
void linkedBinaryTree<T>::makeTree(const T&element, linkedBinaryTree<T>& left, linkedBinaryTree<T>& right) {
    root = new binaryTreeNode<T>(element, left.root, right.root);
    treeSize = left.treeSize + right.treeSize + 1;
    left.root = NULL;
    right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template <class T>
linkedBinaryTree<T>& linkedBinaryTree<T>::removeLeftSubtree() {
    if (treeSize == 0) {
        stringstream s;
        s << "tree is empty." << endl;
        throw range_error(s.str());
    }
    linkedBinaryTree<T> leftSubtree;
    leftSubtree.root = root->leftChild;
    leftSubtree.treeSize= countNode(leftSubtree.root);
    treeSize -= leftSubtree.treeSize;
    root->leftChild = NULL;
    return leftSubtree;
}

template <class T>
linkedBinaryTree<T>& linkedBinaryTree<T>::removeRightSubtree() {
    if (treeSize == 0) {
        stringstream s;
        s << "tree is empty." << endl;
        throw range_error(s.str());
    }
    linkedBinaryTree<T> rightSubtree;
    rightSubtree.root = root->rightChild;
    rightSubtree.treeSize = countNode(rightSubtree.root);
    treeSize -= rightSubtree.treeSize;
    root->rightChild = NULL;
    return rightSubtree;
}


template <class T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T> *t) {
    if (t != NULL) {
        visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template <class T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T> *t) {
    if (t != NULL) {
        inOrder(t->leftChild);
        visit(t);
        inOrder(t->rightChild);
    }
}

template <class T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T> *t) {
    if (t != NULL) {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        visit(t);
    }
}

template <class T>
void linkedBinaryTree<T>::levelOrder(binaryTreeNode<T> *t) {
    queue<binaryTreeNode<T>*> q;
    while (true) {
        visit(t);
        if (t->leftChild != NULL) q.push(t->leftChild);
        if (t->rightChild != NULL) q.push(t->rightChild);
        if (!q.empty()) t = q.front();
        else break;
        q.pop();
    }
}

template <class T>
int linkedBinaryTree<T>::height(binaryTreeNode<T> *t) {
    if (t == NULL) return 0;
    int hl = height(t->leftChild);
    int hr = height(t->rightChild);
    if (hl > hr) return hl+1;
    else return hr+1;
}

template <class T>
void linkedBinaryTree<T>::preOrderUnRecursive(binaryTreeNode<T> *t) {
    stack<binaryTreeNode<T>*> s;
    binaryTreeNode<T> *p = t;
    while (p != NULL || !s.empty()) {
        while (p != NULL) {
            visit(p);
            s.push(p);
            p = p->leftChild;
        }
        if (!s.empty()) {
            p = s.top();
            p = p->rightChild;
            s.pop();
        }
    }
}

template <class T>
void linkedBinaryTree<T>::inOrderUnRecursive(binaryTreeNode<T> *t) {
    stack<binaryTreeNode<T>*> s;
    binaryTreeNode<T> *p = t;
    while (p != NULL || !s.empty()) {
        while (p != NULL) {
            s.push(p);
            p = p->leftChild;
        }
        if (!s.empty()) {
            p = s.top();
            visit(p);
            p = p->rightChild;
            s.pop();
        }
    }
}

template <class T>
void linkedBinaryTree<T>::postOrderUnRecursive(binaryTreeNode<T> *t) {
    stack<binaryTreeNode<T>*> s;
    binaryTreeNode<T> *p = t;
    binaryTreeNode<T> *pre = NULL; // 标记前一个访问过的结点
    while (p != NULL || !s.empty()) { // 结点为空且栈为空时才能结束
        while (p != NULL) {
            s.push(p);
            p = p->leftChild;
        }
        if (!s.empty()) {
            p = s.top();
            if (p->rightChild == NULL || p->rightChild == pre) { //右孩子为空或者右孩子已经访问过，才能访问该结点
                visit(p);
                pre = p; // 访问过后就让pre指向它
                s.pop();
                p = NULL; // 本来应该再次pop,但是这要检查栈是否空. 因此直接让p=NULL,来触发if(!s.empty()){}这个语句块.
            }
            else {
                p = p->rightChild;
            }
        }
    }
}

#endif // !linkedBinaryTree_
