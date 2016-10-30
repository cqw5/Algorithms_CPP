/*! Author: qwchen
 *! Date: 2016-9-21
 * 
 * 基于链表实现的队列Queue，没有头结点
 */

#ifndef linkedQueue_
#define linkedQueue_

#include <sstream>
#include "Queue.h"

using namespace std;

// 链表结点
template <class T>
struct chainNode {
    T element;
    chainNode *next;
    chainNode(T theElem){
        element = theElem;
    }
};

template <class T>
class linkedQueue : public queue<T> {
public:
    linkedQueue();
    ~linkedQueue();
    bool empty() const;           // 当队列为空时，返回true
    int size() const;             // 返回队列中元素的个数【注意：是元素个数，不是容量】
    T& front();                   // 返回头元素的引用
    T& back();                    // 返回尾元素的引用
    void pop();                   // 删除首元素
    void push(const T &theElem);  // 把元素theElem加入队尾
private:
    chainNode<T> *queueFront;
    chainNode<T> *queueBack;
    int queueSize;
};

template <class T>
linkedQueue<T>::linkedQueue() {
    queueFront = NULL;
    queueBack = NULL;
    queueSize = 0;
}

template <class T>
linkedQueue<T>::~linkedQueue() {
    while (!queueFront) {
        queueBack = queueFront->next;
        delete queueFront;
        queueFront = queueBack;
    }
}

template <class T>
bool linkedQueue<T>::empty() const {
    return queueSize == 0;
}

template <class T>
int linkedQueue<T>::size() const {
    return queueSize;
}

template <class T>
T& linkedQueue<T>::front() {
    if (empty()) {
        stringstream s;
        s << "Queue is empty" << endl;
        throw range_error(s.str());
    }
    return queueFront->element;
}

template <class T>
T& linkedQueue<T>::back() {
    if (empty()) {
        stringstream s;
        s << "Queue is empty" << endl;
        throw range_error(s.str());
    }
    return queueBack->element;
}

template <class T>
void linkedQueue<T>::pop() {
    if (empty()) {
        stringstream s;
        s << "Queue is empty" << endl;
        throw range_error(s.str());
    }
    chainNode<T> *deleteNode = queueFront;
    queueFront = queueFront->next;
    delete deleteNode;
    deleteNode = NULL;
    queueSize--;
}

template <class T>
void linkedQueue<T>::push(const T &theElem) {
    chainNode<T> *newNode = new chainNode<T>(theElem);
    if (empty()) {
        queueFront = queueBack = newNode;
    }
    else {
        queueBack->next = newNode;
        queueBack = newNode;
    }
    queueSize++;
}

#endif // !linkedQueue_
