/*! Author: qwchen
 *! Date: 2016-10-10
 * 测试基于链表实现的二叉树
 */

#include <iostream>
#include "linkedBinaryTree.h"

using namespace std;

void testLinkedBinaryTree() {
    // 创建二叉树
    linkedBinaryTree<int> a, x, y, z;
    y.makeTree(1, a, a);
    z.makeTree(2, a, a);
    x.makeTree(3, y, z);
    y.makeTree(4, x, a);
    
    // 二叉树结点
     cout << "Number of nodes = ";
    cout << y.size() << endl;

    // 二叉树高度
    cout << "height = ";
    cout << y.height() << endl;
    
    // 先序遍历
    cout << "PreOrder sequence is (Recursive): ";   // 递归
    y.preOrder();
    cout << "PreOrder sequence is (UnRecursive): "; // 非递归
    y.preOrderUnRecursive();

    // 中序遍历
    cout << "InOrder sequence is (Recursive): ";    // 递归
    y.inOrder();
    cout << "InOrder sequence is (UnRecursive): ";  // 非递归
    y.inOrderUnRecursive();

    // 后序遍历
    cout << "PostOrder sequence is (Recursive): ";   // 递归
    y.postOrder();
    cout << "PostOrder sequence is (UnRecursive): "; // 非递归
    y.postOrderUnRecursive();

    // 层次遍历
    cout << "Level order sequence is : ";
    y.levelOrder();
}

int main(){
    testLinkedBinaryTree();
    return 0;
}