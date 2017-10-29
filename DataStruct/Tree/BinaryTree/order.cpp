/*! Author: qwchen
 *! Date  : 2017-10-29
 *  二叉树的
 *  - 先序遍历：递归、非递归
 *  - 中序遍历：递归、非递归
 *  - 后序遍历：递归、非递归
 *  - 层次遍历：非递归
 */

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template <class T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T theVal):val(theVal),left(nullptr),right(nullptr){}
};


/*
 * 先序遍历，递归版本
 * 思路：先访问根结点，再访问左子树，最后访问右子树
 */
template <class T>
void preOrder(TreeNode<T> *t) {
    if (t != NULL) {
        visit(t);
        preOrder(t->left);
        preOrder(t->right);
    }
}

/*
 * 先序遍历，非递归版本
 * 思路：对于任一结点，其可看做是根结点，因此可以直接访问，访问完之后，若其左孩子不为空，按相同规则访问它的左子树；
 *      当访问完其左子树时，再访问它的右子树。
 */
template <class T>
void preOrderUnRecursive(TreeNode<T> *t) {
    stack<TreeNode<T>*> s;
    TreeNode<T> *p = t;
    while (p != NULL || !s.empty()) {
        while (p != NULL) {
            visit(p);
            s.push(p);
            p = p->left;
        }
        if (!s.empty()) {
            p = s.top();
            p = p->right;
            s.pop();
        }
    }
}


/*
 * 中序遍历，递归版本
 * 思路：先访问左子树，再访问根结点，最后访问右子树
 */
template <class T>
void inOrder(TreeNode<T> *t) {
    if (t != NULL) {
        inOrder(t->left);
        visit(t);
        inOrder(t->right);
    }
}

/*
 * 中序遍历，非递归版本
 * 思路：对于任一结点，优先访问其左孩子，而左孩子结点又可以看做一根结点，然后继续访问其左孩子结点，
 *      直到遇到左孩子结点为空的结点才进行访问，然后访问其右子树。
 */
template <class T>
void inOrderUnRecursive(TreeNode<T> *t) {
    stack<TreeNode<T>*> s;
    TreeNode<T> *p = t;
    while (p != NULL || !s.empty()) {
        while (p != NULL) {
            s.push(p);
            p = p->left;
        }
        if (!s.empty()) {
            p = s.top();
            visit(p);
            p = p->right;
            s.pop();
        }
    }
}


/*
 * 后序遍历，递归版本
 * 思路：先访问左子树，再访问右子树，最后访问根结点
 */
template <class T>
void postOrder(TreeNode<T> *t) {
    if (t != NULL) {
        postOrder(t->left);
        postOrder(t->right);
        visit(t);
    }
}

/*
 * 后序遍历，非递归版本
 * 思路：对于任一结点P，如果P不存在左孩子和右孩子，则可以直接访问它；
 *      或者P存在左孩子或者右孩子，但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。
 */
template <class T>
void postOrderUnRecursive(TreeNode<T> *t) {
    stack<TreeNode<T>*> s;
    TreeNode<T> *p = t;
    TreeNode<T> *pre = NULL; // 标记前一个访问过的结点
    while (p != NULL || !s.empty()) { // 结点为空且栈为空时才能结束
        while (p != NULL) {
            s.push(p);
            p = p->left;
        }
        if (!s.empty()) {
            p = s.top();
            if (p->right == NULL || p->right == pre) { //右孩子为空或者右孩子已经访问过，才能访问该结点
                visit(p);
                pre = p; // 访问过后就让pre指向它
                s.pop();
                p = NULL; // 本来应该再次pop,但是这要检查栈是否空. 因此直接让p=NULL,来触发if(!s.empty()){}这个语句块.
            }
            else {
                p = p->right;
            }
        }
    }
}


/*
 * 层次遍历
 * 思路：层次遍历是一层一层访问树的结点，可以用队列来实现
 */
template <class T>
void levelOrder(TreeNode<T> *t) {
    queue<TreeNode<T>*> q;
    while (true) {
        visit(t);
        if (t->left != NULL) q.push(t->left);
        if (t->right != NULL) q.push(t->right);
        if (!q.empty()) t = q.front();
        else break;
        q.pop();
    }
}


