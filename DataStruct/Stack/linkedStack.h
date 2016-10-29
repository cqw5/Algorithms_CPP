/*! Author: qwchen
 *! Date: 2016-9-18
 * 基于链表实现的栈
 */

#ifndef linkedStack_
#define linkedStack_

#include <sstream>
#include "stack.h"

using namespace std;

template <class T>
struct chainNode{
    T element;
    chainNode *next;
    chainNode(T theElem){
        element = theElem;
    }
};

template <class T>
class linkedStack: public stack<T> {
public:
    linkedStack();
    ~linkedStack();
    bool empty() const;           // 当栈为空时返回true
    int size() const;             // 返回栈中元素的个数
    T& top() const;               // 返回栈顶元素的引用
    void pop();                   // 删除栈顶元素
    void push(const T& theElem);  // 将元素theElem压入栈顶
private:
    chainNode<T>* stackTop;       // 栈，不带头结点的单向链表，头指针为栈顶指针
    int stackSize;                // 栈大小
};

template <class T>
linkedStack<T>::linkedStack(){
    stackTop = NULL;
    stackSize = 0;
}

template <class T>
linkedStack<T>::~linkedStack(){
    chainNode<T>* currentNode = stackTop;
    while (stackTop != NULL) {
        currentNode = stackTop->next;
        delete stackTop;
        stackTop = currentNode;
    }
}

template <class T>
bool linkedStack<T>::empty() const {
    return stackSize == 0;
}

template <class T>
int linkedStack<T>::size() const {
    return stackSize;
}

template <class T>
T& linkedStack<T>::top() const {
    if (empty()) {
        stringstream s;
        s << "Stack is empty" << endl;
        throw range_error(s.str());
    }
    return stackTop->element;
}

template <class T>
void linkedStack<T>::pop() {
    if (empty()) {
        stringstream s;
        s << "Stack is empty" << endl;
        throw range_error(s.str());
    }
    chainNode<T> *deleteNode = stackTop;
    stackTop = stackTop->next;
    delete deleteNode;
    deleteNode = NULL;
    stackSize--;
}

template <class T>
void linkedStack<T>::push(const T& theElem) {
    chainNode<T> *newNode = new chainNode<T>(theElem);
    newNode->next = stackTop;
    stackTop = newNode;
    stackSize++;
}

#endif // !linkedStack_