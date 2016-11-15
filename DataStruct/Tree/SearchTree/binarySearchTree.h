/*! Author: qwchen
 *! Date: 2016-10-10
 * 二叉搜索树
 */

#ifndef binarySearchTree_
#define binarySearchTree_

#include <iostream>

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

template <class K, class E>
class binarySearchTree {
public:
    binarySearchTree();
    ~binarySearchTree();
    int size() const;
    pair<const K, E>* find(const K& theKey) const; // 查找结点
    pair<const K, E>* findLE(const K& theKey) const; // 查找小于等于theKey的最大元素
    pair<const K, E>* findGE(const K& theKey) const; // 查找大于等于theKey的最小元素
    void insert(const pair<const K, E>& thePair);  // 插入结点
    void erase(const K& theKey);                   // 删除结点
    void ascend();                                 // 升序输出结点

private:
    binaryTreeNode<pair<const K, E>> *root; // 树的根节点
    int treeSize;                           // 树的节点个数
    void postOrderDeleteTree(binaryTreeNode<pair<const K, E>>* t); // 按后序遍历的方式删除树
    void inOrderOutputTree(binaryTreeNode<pair<const K, E>>* t);   // 按中序遍历的方式输出树
};

template <class K, class E>
binarySearchTree<K, E>::binarySearchTree(){
    root = NULL;
    treeSize = 0;
}

template <class K, class E>
binarySearchTree<K, E>::~binarySearchTree(){
    postOrderDeleteTree(root);
    root = NULL;
}

template <class K, class E>
void binarySearchTree<K, E>::postOrderDeleteTree(binaryTreeNode<pair<const K, E>>* t){
    if (t != NULL){
        postOrderDeleteTree(t->leftChild);
        postOrderDeleteTree(t->rightChild);
        delete t;
    }
}

template <class K, class E>
void binarySearchTree<K, E>::inOrderOutputTree(binaryTreeNode<pair<const K, E>>* t){
    if (t != NULL){
        inOrderOutputTree(t->leftChild);
        cout << "(" << t->element.first << ", " << t->element.second << ") ";
        inOrderOutputTree(t->rightChild);
    }
}

template <class K, class E>
int binarySearchTree<K, E>::size() const {
    return treeSize;
}

template <class K, class E>
pair<const K, E>* binarySearchTree<K, E>::find(const K &theKey) const {
    binaryTreeNode<pair<const K, E>> *p = root;
    while (p != NULL) {
        if (theKey < p->element.first) p = p->leftChild;       // theKey < 根的关键字
        else if (theKey > p->element.first) p = p->rightChild; // theKey > 根的关键字
        else return &p->element;                               // theKey = 根的关键字
    }
    return NULL;
}

template <class K, class E>
pair<const K, E>* binarySearchTree<K, E>::findLE(const K& theKey) const {
    binaryTreeNode<pair<const K, E>> *p = root;
    pair<const K, E> *bestElement = NULL; // 目前查找到的元素，其关键字是小于等于theKey的最大元素
    while(p != NULL){
        // p->element是一个候选者吗？
        if (p->element.first <= theKey){
            // 是，p->element是比bestElement更好的候选者
            bestElement = &p->element;
            p = p->rightChild;
        } else {
            // 不是，p->element.first太大
            p = p->leftChild;
        }
    }
    return bestElement;
}

template <class K, class E>
pair<const K, E>* binarySearchTree<K, E>::findGE(const K& theKey) const {
    binaryTreeNode<pair<const K, E>> *p = root;
    pair<const K, E> *bestElement = NULL;
    while(p != NULL){
        if (p->element.first >= theKey){
            bestElement = &p->element;
            p = p->leftChild;
        } else {
            p = p->rightChild;
        }
    }
    return bestElement;
}

template <class K, class E>
void binarySearchTree<K, E>::insert(const pair<const K, E> &thePair) {
    binaryTreeNode<pair<const K, E>> *p = root, 
                                     *pp = NULL;    // pp指向p的父节点
    while (p != NULL) {
        if (thePair.first < p->element.first) {
            pp = p;
            p = p->leftChild;
        }
        else if (thePair.first > p->element.first) {
            pp = p;
            p = p->rightChild;
        }
        else { // 如果有相同的key的结点，直接替换
            p->element.second = thePair.second;
            return;
        }
    }
    binaryTreeNode<pair<const K, E>> *newNode = new binaryTreeNode<pair<const K, E>>(thePair);
    if (root != NULL) { // 树本身不为空，pp的子节点就是插入位置（左孩子还是右孩子）
        if (thePair.first < pp->element.first) pp->leftChild = newNode;
        else pp->rightChild = newNode;
    }
    else { // 树本身为空
        root = newNode;
    }
    treeSize++;
}

template <class K, class E>
void binarySearchTree<K, E>::erase(const K &theKey) {
    binaryTreeNode<pair<const K, E>> *p = root,
                                     *pp = NULL;
    // 搜索到待删除的结点
    while (p != NULL) {
        if (theKey < p->element.first) {
            pp = p;
            p = p->leftChild;
        }
        else if (theKey > p->element.first) {
            pp = p;
            p = p->rightChild;
        }
        else break;
    }
    // 如果待删除的结点不存在，直接返回
    if (p == NULL)
        return;
    // 如果待删除的结点存在左右子树（第3种情况）
    if (p->leftChild != NULL && p->rightChild != NULL) {
        // 先寻找左子树最大的结点
        binaryTreeNode<pair<const K, E>> *s = p->leftChild,
                                         *ps = p;
        while (s->rightChild) {
            ps = s;
            s = s->rightChild;
        }
        binaryTreeNode<pair<const K, E>> *q = new binaryTreeNode<pair<const K, E>>(s->element, p->leftChild, p->rightChild);
        // 修改待删除结点的父结点的孩子指针的指向
        if (p == root) {
            root = q;
        }
        else {
            if (p == pp->leftChild)
                pp->leftChild = q;
            else
                pp->rightChild = q;
        }
        // 问题转化为删除结点s(存在0或1个子树的结点)，重新让p指向s，pp指向s的父节点，问题就是删除p的问题（此时p是第1或第2种情况了）
        if (ps == p) pp = q; // 左孩子没有右子树
        else pp = ps;
        delete p;
        p = s;
    }
    // 如果待删除的结点最多只存在一个子树
    binaryTreeNode<pair<const K, E>> *c = NULL;
    if (p->leftChild != NULL) c = p->leftChild;
    else c = p->rightChild;
    // 如果待删除的结点是根结点
    if (p == root) {
        root = c;
    }
    else {
        if (p == pp->leftChild) pp->leftChild = c;
        else pp->rightChild = c;
    }
    delete p;
    treeSize--;
}

template <class K, class E>
void binarySearchTree<K, E>::ascend(){
    inOrderOutputTree(root);
    cout << endl;
}


#endif // !binarySearchTree_