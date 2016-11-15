/*! Author: qwchen
 *! Date: 2016-10-10
 * 测试二叉搜索树
 */

#include <iostream>
#include "binarySearchTree.h"

using namespace std;

void testBinarySearchTree()
{
    binarySearchTree<int, char> y;
    y.insert(pair<int, char>(1, 'a'));
    y.insert(pair<int, char>(6, 'c'));
    y.insert(pair<int, char>(4, 'b'));
    y.insert(pair<int, char>(8, 'd'));
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are : ";
    y.ascend();
    
    pair<const int, char> *s = y.find(4);
    cout << "Search for 4 succeeds " << endl;
    cout << s->first << " " << s->second << endl;
    s = y.findLE(5);
    cout << "Search for <= 5 succeeds " << endl;
    cout << s->first << " " << s->second << endl;
    s = y.findGE(5);
    cout << "Search for >= 5 succeeds " << endl;
    cout << s->first << " " << s->second << endl;
    y.erase(4);
    cout << "4 deleted " << endl;
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are : ";
    y.ascend();
    
    s = y.find(8);
    cout << "Search for 8 succeeds " << endl;
    cout << s->first << ' ' << s->second << endl;
    y.erase(8);
    cout << "8 deleted " << endl;
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are : ";
    y.ascend();
    
    s = y.find(6);
    cout << "Search for 6 succeeds " << endl;
    cout << s->first << ' ' << s->second << endl;
    y.erase(6);
    cout << "6 deleted " << endl;
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are : ";
    y.ascend();

    s = y.find(1);
    cout << "Search for 1 succeeds " << endl;
    cout << s->first << ' ' << s->second << endl;
    y.erase(1);
    cout << "1 deleted " << endl;
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are" << endl;
    y.ascend();
    
}

int main(){
    testBinarySearchTree();
    return 0;
}