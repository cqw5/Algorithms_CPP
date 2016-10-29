/*! Author: qwchen
 *! Date: 2016-9-18
 * 基于数组实现的栈stack
 */

#ifndef arrayStack_
#define arrayStack_

#include <iostream>
#include <sstream>
#include "stack.h"

using namespace std;

template <class T>
class arrayStack : public stack<T> {
public:
    arrayStack(int initCapacity = 10);
    ~arrayStack();
    bool empty() const;           // 当栈为空时返回true
    int size() const;             // 返回栈中元素的个数
    T& top() const;               // 返回栈顶元素的引用
    void pop();                   // 删除栈顶元素
    void push(const T& theElem);  // 将元素theElem压入栈顶
private:
    T *stack;         // 元素数组
    int stackTop;     // 栈顶，指向栈顶元素，初始为-1
    int arrayLength;  // 栈的容量
};

template <class T>
arrayStack<T>::arrayStack(int initCapacity) {
    if (initCapacity < 0) {
        stringstream s;
        s << "initCapacity must be > 0" << endl;
        throw invalid_argument(s.str());
    }
    arrayLength = initCapacity;
    stackTop = -1;
    stack = new T[arrayLength];
}

template <class T>
arrayStack<T>::~arrayStack() {
    delete []stack;
}


template <class T>
bool arrayStack<T>::empty() const {
    return stackTop == -1;
}


template <class T>
int arrayStack<T>::size() const {
    return stackTop + 1;
}

template <class T>
T& arrayStack<T>::top() const {
    if (empty()) {
        stringstream s;
        s << "Stack is empty" << endl;
        throw range_error(s.str());
    }
    return stack[stackTop];
}

template <class T>
void arrayStack<T>::pop() {
    if (empty()) {
        stringstream s;
        s << "Stack is empty" << endl;
        throw range_error(s.str());
    }
    stack[stackTop--].~T();        // 重点,new出来的都有析构
}

template <class T>
void arrayStack<T>::push(const T& theElem) {
    // 数组已经满，将数组容量扩大为两倍
    if (stackTop + 1 == arrayLength) {
        T *tmp = new T[2 * arrayLength];
        for (int i = 0; i < arrayLength; i++){
            tmp[i] = stack[i];
        }
        delete []stack;
        stack = tmp;
        arrayLength *= 2;
    }
    stack[++stackTop] = theElem;
}


#endif // !arrayStack_
