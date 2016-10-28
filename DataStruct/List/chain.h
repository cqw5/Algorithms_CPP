/*! Author: qwchen
 *! Date: 2016-9-14
 * 线性表的链表描述
 */

#ifndef chain_
#define chain_

#include <iostream>
#include <sstream>
#include "linearList.h"

using namespace std;

// 链表结点
template <class T>
struct chainNode {
    T element;          // 链表元素
    chainNode<T> *next; // 链表的next指针

    chainNode(){}
    chainNode(const T& element){
        this->element = element;
        this->next = NULL;
    }
    chainNode(const T& element, chainNode<T>* next){
        this->element = element;
        this->next = next;
    }
};

// 链表
template <class T>
class chain : public linearList<T> {
public:
    chain();                  // 构造函数
    chain(const chain<T> &);  // 拷贝构造函数
    ~chain();                 // 析构函数

    bool empty() const;                     // 返回当链表为空时，返回true
    int size() const;                       // 返回链表元素的个数
    int capacity() const;                   // 没用，只是为了实现抽象类linearList的方法
    T& get(int theIndex) const;             // 返回索引为theIndex的元素
    int indexOf(const T &theElement) const;    // 返回元素theElement第一次出现时的索引
    void erase(int theIndex);               // 删除索引为theIndex的元素
    void insert(int theIndex, const T &theElement);    // 把theElement插入线性表中索引为theIndex的位置上
    void output(ostream &out) const;        // 把线性表插入到输出流

private:
    chainNode<T> *firstNode;    // 头指针，指向列表的第一个结点
    int m_iSize;
};

template <class T>
chain<T>::chain() {
    firstNode = NULL;
    m_iSize = 0;
}

template <class T>
chain<T>::chain(const chain<T> &theList) {
    m_iSize = theList.m_iSize;
    if (m_iSize == 0) { //考虑边界值，当原来的链表为空
        firstNode = NULL;
        return;
    }
    // 链表的拷贝：
    // theList.firstNode指向源链表，firstNode指向目的链表
    // sourceNode指向源链表的当前元素，targetNode指向目的链表的当前元素
    chainNode<T> *sourceNode = theList.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    chainNode<T> *targetNode = firstNode;
    sourceNode = sourceNode->next;
    while (sourceNode != NULL) {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;
}

template <class T>
chain<T>::~chain() {
    while (firstNode != NULL) {
        // chainNode<T> *nextNode = firstNode;  这种写法就错，导致内存泄露
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
bool chain<T>::empty() const{ 
    return m_iSize == 0; 
}

template <class T>
int chain<T>::size() const { 
    return m_iSize;  
}

template <class T>
int chain<T>::capacity() const { 
    return m_iSize; 
}

template <class T>
T& chain<T>::get(int theIndex) const {
    if (theIndex < 0 || theIndex >= m_iSize) {
        stringstream s;
        s << "index = " << theIndex << " size = " << m_iSize << endl;
        throw invalid_argument(s.str());
    }
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

template <class T>
int chain<T>::indexOf(const T &theElement) const {
    chainNode<T> *currentNode = firstNode;
    int index = 0;
    while (currentNode != NULL && currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == NULL) return -1;
    else return index;
}

template <class T>
void chain<T>::erase(int theIndex) {
    if (theIndex < 0 || theIndex >= m_iSize) {
        stringstream s;
        s << "index = " << theIndex << " size = " << m_iSize << endl;
        throw invalid_argument(s.str());
    }
    chainNode<T> *deleteNode;
    // 对于没有头结点的链表，要注意删除位置是不是首结点
    if (0 == theIndex) { // 如果删除的是首节点
        deleteNode = firstNode;
        firstNode = firstNode->next;
    } else {
        chainNode<T> *currentNode = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            currentNode = currentNode->next;
        }
        deleteNode = currentNode->next;
        currentNode->next = currentNode->next->next;
    }
    delete deleteNode;
    m_iSize--;
}

template <class T>
void chain<T>::insert(int theIndex, const T &theElement) {
    if (theIndex < 0 || theIndex > m_iSize) {
        stringstream s;
        s << "index = " << theIndex << " size = " << m_iSize;
        throw invalid_argument(s.str());
    }
    chainNode<T> *insertNode = new chainNode<T>(theElement);
    // 对于没有头结点的链表，要注意插入位置是不是首结点
    if (0 == theIndex) { // 如果是在首节点插入
        insertNode->next = firstNode;
        firstNode = insertNode;
    } else { // 如果不是在首节点插入
        chainNode<T> *currentNode = firstNode;
        for (int i = 0; i < theIndex - 1; i++) {
            currentNode = currentNode->next;
        }
        insertNode->next = currentNode->next;
        currentNode -> next = insertNode;
    }
    m_iSize++;  // 注意别忘了
}

template <class T>
void chain<T>::output(ostream &out) const {
    for (chainNode<T> *currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

template <class T>
ostream& operator<<(ostream& out, const chain<T> &x) {
    x.output(out);
    return out;
}

#endif // !chain_
