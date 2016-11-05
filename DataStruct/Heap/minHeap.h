/*! Author: qwchen
 *! Date: 2016-9-28
 * 用数组实现的小顶堆， 数组下标0不用，从下标1开始
 */

#ifndef minHeap_
#define minHeap_

#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "heap.h"

using namespace std;

template <class T>
class minHeap: public heap<T> {
public:
    minHeap(int capacity = 10) {
        if (capacity < 2) {
            stringstream s;
            s << "capacity must be > 2";
            throw invalid_argument(s.str());
        }
        heap = new T[capacity];
        arrayLength = capacity;
        heapSize = 0;
    }
    ~minHeap() { delete[]heap; }
    bool empty() const {  // 返回true，当且仅当队列为空
        return heapSize == 0;
    }
    int size() const {    // 返回队列的元素个数
        return heapSize;
    }
    const T& top() {      // 返回优先级最大的元素的引用
        if (empty()) {
            stringstream s;
            s << "heap is empty." << endl;
            throw range_error(s.str());
        }
        return heap[1];
    }
    void push(const T& theElement);            // 插入元素
    void pop();                                // 删除队首元素
    void initialize(T *theHeap, int theSize);  // 初始化堆
    void deactivateArray() {                   // 保存数组
        heap = NULL; arrayLength = heapSize = 0;
    }
    void output(ostream& out) const;
private:
    T *heap;         // 用数组表示堆
    int arrayLength; // 数组的长度
    int heapSize;    // 堆元素的个数
};

template <class T>
void minHeap<T>::push(const T& theElement) {
    // 数组已满
    if (arrayLength == heapSize + 1) {
        T *temp = new T[arrayLength * 2];
        copy(heap, heap + arrayLength, temp);
        delete[]heap;
        heap = temp;
    }
    int currentNode = ++heapSize;  // currentNode指定要插入的位置
    while (currentNode != 1 && heap[currentNode / 2] > theElement) {
        heap[currentNode] = heap[currentNode / 2];
        currentNode /= 2;
    }
    heap[currentNode] = theElement;
}

template <class T>
void minHeap<T>::pop() {
    // pop时不能为空
    if (empty()) {
        stringstream s;
        s << "heap is empty." << endl;
        throw range_error(s.str());
    }
    int currentNode = 1;            // 当前结点
    T lastElement = heap[heapSize]; // 取出最后一个元素
    heap[heapSize].~T();
    heapSize--;
    int child = 2;
    while (child <= heapSize) {
        // 找出最小的孩子
        if (child + 1 <= heapSize && heap[child] > heap[child + 1]) child++;
        // 如果孩子都没有小于父节点，停止
        if (heap[child] >= lastElement) break;
        heap[currentNode] = heap[child];
        currentNode = child;
        child = 2 * currentNode;
    }
    heap[currentNode] = lastElement;
}

template <class T>
void minHeap<T>::initialize(T *theHeap, int theSize) {
    delete[]heap;
    heap = theHeap;
    heapSize = theSize;
    for (int root = heapSize / 2; root > 0; root--) {
        T rootElement = heap[root];
        int currentNode = root;
        int child = 2 * currentNode;
        while (child <= heapSize) {
            if (child < heapSize && heap[child] > heap[child + 1]) child++;
            if (heap[child] >= rootElement) break;
            heap[currentNode] = heap[child];
            currentNode = child;
            child = 2 * currentNode;
        }
        heap[currentNode] = rootElement;
    }
}

template<class T>
void minHeap<T>::output(ostream& out) const {
    copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, "  "));
}

template <class T>
ostream& operator<<(ostream& out, const minHeap<T>& x) {
    x.output(out); return out;
}

#endif // !minHeap_