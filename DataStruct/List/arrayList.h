/*! Author: qwchen
 *! Date: 2016-9-14
 * 线性表的数组描述
 */

#ifndef arrayList_
#define arrayList_

#include <iostream>
#include <sstream>
#include <algorithm>
#include "linearList.h"

using namespace std;

template <class T>
class arrayList : public linearList<T> {
public:
    arrayList(int capacity = 10);         // 构造函数
    arrayList(const arrayList<T> &);      // 拷贝构造函数
    ~arrayList();                         // 析构函数

    bool empty() const;                   // 返回当线性表为空时，返回true 
    int size() const;                     // 返回线性表元素的个数
    int capacity() const;                 // 返回线性表容量
    T& get(int theIndex) const;           // 返回索引为theIndex的元素
    int indexOf(const T &theElem) const;  // 返回元素theElement第一次出现时的索引
    void erase(int theIndex);             // 删除索引为theIndex的元素
    void insert(int theIndex, const T &theElem);  // 把theElement插入线性表中索引为theIndex的位置上
    void output(ostream &out) const;      // 把线性表插入到输出流

private:
	bool full() const;                    // 当线性表数组满的时候，返回true
    T *m_pBuffer;       // 存储线性表元素的一维数组
    int m_iCapacity;    // 一维数组的容量
    int m_iSize;        // 线性表元素个数
};


template <class T>
arrayList<T>::arrayList(int capacity) {
    if (capacity < 1) {
        stringstream s;
        s << "illegal parameter:  Initial capacity = " << capacity << " Must be > 0";
        throw invalid_argument(s.str());
    }
    m_pBuffer = new T[capacity];
    m_iCapacity = capacity;
    m_iSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList) {
    m_iCapacity = theList.m_iCapacity;
    m_iSize = theList.m_iSize;
    m_pBuffer = new T[m_iCapacity];
    copy(theList.m_pBuffer, theList.m_pBuffer + m_iCapacity, m_pBuffer);
}

template <class T>
arrayList<T>::~arrayList() {
    delete []m_pBuffer;
}


template <class T>
bool arrayList<T>::empty() const {
    return m_iSize == 0;
}

template <class T>
bool arrayList<T>::full() const { 
    return m_iSize == m_iCapacity; 
}

template <class T>
int arrayList<T>::size() const { 
    return m_iSize; 
}

template <class T>
int arrayList<T>::capacity() const { 
    return m_iCapacity; 
}

template <class T>
T& arrayList<T>::get(int theIndex) const {
    if (theIndex < 0 || theIndex >= m_iSize) {
        stringstream s;
        s << "index = " << theIndex << " size = " << m_iSize;
        throw invalid_argument(s.str());
    }
    return m_pBuffer[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T &theElem) const {
    for (int i = 0; i < m_iSize; i++){
        if (m_pBuffer[i] == theElem){
            return i;
        }
    }
    return -1;   // 找不到
}

template <class T>
void arrayList<T>::erase(int theIndex) {
    if (theIndex < 0 || theIndex >= m_iSize) {
        stringstream s;
        s << "index = " << theIndex << " size = " << m_iSize;
        throw invalid_argument(s.str());
    }
    copy(m_pBuffer + theIndex + 1, m_pBuffer + m_iSize, m_pBuffer + theIndex);
    m_pBuffer[--m_iSize].~T();
}

template <class T>
void arrayList<T>::insert(int theIndex, const T& theElem) {
    if (theIndex < 0 || theIndex > m_iSize) {
        stringstream s;
        s << "index = " << theIndex << " size = " << m_iSize;
        throw invalid_argument(s.str());
    }
    if (full()) {
    	// 将数组大小加倍
        T *tmp = new T[2 * m_iCapacity];
        copy(m_pBuffer, m_pBuffer + m_iCapacity, tmp);
        delete m_pBuffer;
        m_pBuffer = tmp;
        tmp = NULL;
        m_iCapacity *= 2;
    }
    copy_backward(m_pBuffer + theIndex, m_pBuffer + m_iSize, m_pBuffer + m_iSize + 1);
    m_pBuffer[theIndex] = theElem;
    m_iSize++;
}

template <class T>
void arrayList<T>::output(ostream &out) const {
    for (int i = 0; i < m_iSize; i++){
        out << m_pBuffer[i] << " ";
    }
}

template <class T>
ostream& operator<<(ostream& out, const arrayList<T> &x) {
    x.output(out);
    return out;
}

#endif
