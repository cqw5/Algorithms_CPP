/*! Author: qwchen
 *! Date: 2016-11-15
 * 测试字典树
 */

#include <iostream>
#include "Trie.h"

using namespace std;

void testTrie(){
    Trie t;
    cout << "insert something" << endl;
    cout << "insert some" << endl;
    cout << "insert hello world" << endl;
    t.insert("something");
    t.insert("some");
    t.insert("hello world");

    if (t.search("hello world")){
        cout << "hello world exist" << endl;
    } else {
        cout << "hello world doesn't exist" << endl;
    }
    if (t.search("hello world2")){
        cout << "hello world2 exist" << endl;
    } else {
        cout << "hello world2 doesn't exist" << endl;
    }

    if (t.startsWith("some")){
        cout << "some is prefix" << endl;
    } else {
        cout << "some isn't prefix" << endl;
    }
    if (t.startsWith("some2")){
        cout << "some2 is prefix" << endl;
    } else {
        cout << "some2 isn't prefix" << endl;
    }

}

int main(){
    testTrie();
    return 0;
}