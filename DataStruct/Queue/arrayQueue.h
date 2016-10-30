/*! Author: qwchen
 *! Date: 2016-9-21
 * 
 * 用数组实现的队列（带头结点的循环队列）
 * 头指针指向头结点，即第一个元素的前一个结点
 * 尾指针指向最后一个元素
 */

#ifndef arrayQueue_
#define arrayQueue_

#include <sstream>
#include <iostream>
#include <algorithm>
#include "queue.h"

using namespace std;

template <class T>
class arrayQueue : public queue<T> {
public:
    arrayQueue(int capacity = 10);
    ~arrayQueue();
    bool empty() const;            // 当队列为空时，返回true
    int size() const;              // 返回队列中元素的个数【注意：是元素个数，不是容量】
    T& front();                    // 返回头元素的引用
    T& back();                     // 返回尾元素的引用
    void pop();                    // 删除首元素
    void push(const T &theElem);   // 把元素theElem加入队尾
private:
    T *queue;          // 数组存储队列
    int arrayLength;   // 队列的容量【注意：不是元素个数，是容量】
    int theFront;      // 首元素
    int theBack;       // 尾元素
};

template <class T>
arrayQueue<T>::arrayQueue(int capacity) {
    if (capacity <= 0) {
        stringstream s;
        s << "capacity must be > 0" << endl;
        throw invalid_argument(s.str());
    }
    queue = new T[capacity];
    arrayLength = capacity;
    theFront = theBack = 0;
}

template <class T>
arrayQueue<T>::~arrayQueue() {
    delete []queue;
    queue = NULL;
}

template <class T>
bool arrayQueue<T>::empty() const {
    return theFront == theBack;
}

template <class T>
int arrayQueue<T>::size() const {
    return (theBack - theFront + arrayLength) % arrayLength;
}

template <class T>
T& arrayQueue<T>::front() {
    if (empty()) {
        stringstream s;
        s << "Queue is empty" << endl;
        throw range_error(s.str());
    }
    return queue[(theFront + 1) % arrayLength];
}

template <class T>
T& arrayQueue<T>::back() {
    if (empty()) {
        stringstream s;
        s << "Queue is empty" << endl;
        throw range_error(s.str());
    }
    return queue[theBack];
}

template <class T>
void arrayQueue<T>::pop() {
    if (empty()) {
        stringstream s;
        s << "Queue is empty" << endl;
        throw range_error(s.str());
    }
    theFront = (theFront + 1) % arrayLength;
    queue[theFront].~T();
}

template <class T>
void arrayQueue<T>::push(const T &theElem) {
    // 如果数组已满，先扩充数据长度
    if ((theBack + 1) % arrayLength == theFront) {
        T* newQueue = new T[2 * arrayLength];
        if (theFront == 0) {
            copy(queue, queue + arrayLength, newQueue);
        }
        else { // 数组已满，所以除了theFront=0时，不可能出现theFront在theBack前面的情形了
            copy(queue + theFront, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - theFront);
        }
        theFront = 0;
        theBack = arrayLength - 1;
        queue = newQueue;
        arrayLength *= 2;
    }
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElem;
}

#endif // !arrayQueue_
