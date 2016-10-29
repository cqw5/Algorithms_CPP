/*! Author: qwchen
 *! Date: 2016-9-18
 * 测试基于数组实现的栈stack
 */

#include <iostream>
#include "arrayStack.h"

using namespace std;

void testArrayStack() {
    arrayStack<int> s;

    // 增加新元素
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    // 测试 empty和size
    if (s.empty())
        cout << "The Stack is empty" << endl;
    else
        cout << "The Stack is not empty" << endl;
    
    cout << "The Stack size is " << s.size() << endl;
        
    while (!s.empty()){
        cout << "Stack top is " << s.top() << endl;
        s.pop();
        cout << "Poped top element" << endl;
    }
    
    try {
        s.pop();
    }
    catch (exception e) {
        cout << e.what() << endl;
    }
}

int main(){
    testArrayStack();
    return 0;
}