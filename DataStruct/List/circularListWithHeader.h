/*! Author: qwchen
 *! Date: 2016-9-14
 * 带头结点的双向循环链表
 */

#ifndef circularListWithHeader_
#define circularListWithHeader_

#include <iostream>
#include <sstream>

using namespace std;

// 双向结点
template <class T>
struct circularListNode {
    T element;                        // 结点元素
    circularListNode<T> *previous;    // 前向指针
    circularListNode<T> *next;        // 后向指针

    circularListNode() {}
    circularListNode(T theElement) {
        this->element = theElement;
    }
};

// 带头结点的双向循环链表
template <class T>
class circularListWithHeader {
public:
    circularListWithHeader();                                    // 构造函数
    circularListWithHeader(const circularListWithHeader<T> &);   // 拷贝构造函数
    ~circularListWithHeader();                                   // 析构函数
    
    bool empty() const;                             // 判断列表是否为空
    int size() const;                               // 返回链表元素的个数
    T& get(int theIndex) const;                     // 返回索引为theIndex的元素
    int indexOf(const T &theElement) const;         // 返回元素theElement第一次出现时的索引
    void erase(int theIndex);                       // 删除索引为theIndex的元素
    void insert(int theIndex, const T &theElement); // 把theElement插入线性表中索引为theIndex的位置上
    void output(ostream &out) const;                // 把线性表插入到输出流

private:
    void checkIndex(int theIndex) const;            // 检测索引theIndex使用合格, 0 < theIndex < m_iSize
    circularListNode<T> *firstNode;                 // 头结点
    int m_iSize;
};

template <class T>
circularListWithHeader<T>::circularListWithHeader() { //构造函数
    firstNode = new circularListNode<T>();
    firstNode->previous = firstNode;
    firstNode->next = firstNode;
    m_iSize = 0;
}

template <class T>
circularListWithHeader<T>::circularListWithHeader(const circularListWithHeader<T>& theList) {    //拷贝构造函数
    m_iSize = theList.m_iSize;
    if (m_iSize == 0) { //长度为0的话，就只创建头结点
        firstNode = new circularListNode<T>();
        firstNode->previous = firstNode;
        firstNode->next = firstNode;
        return;
    }
    // 链表的拷贝：
    // theList.firstNode指向源链表的头结点，firstNode指向目的链表头结点
    // sourceNode指向源链表的当前元素，targetNode指向目的链表的当前元素
    circularListNode<T> *sourceNode = theList.firstNode->next; //source链表中可移动的指针
    firstNode = new circularListNode<T>();
    circularListNode<T> *targetNode = new circularListNode<T>(sourceNode->element); //targe链表中可移动的指针
    firstNode->next = targetNode;
    targetNode->previous = firstNode;
    sourceNode = sourceNode->next;
    while (sourceNode != theList.firstNode){
        targetNode->next = new circularListNode<T>(sourceNode->element);
        targetNode->next->previous = targetNode;
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = firstNode;
    firstNode->previous = targetNode;
}

template <class T>
circularListWithHeader<T>::~circularListWithHeader() {
    // 先断开循环链表，让最后一个结点的next指针置为NULL
    firstNode->previous->next = NULL;    // 【重点】少了这一行会内存泄露，程序无法运行
    while (firstNode != NULL){
        circularListNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
void circularListWithHeader<T>::checkIndex(int theIndex) const { //检测索引theIndex使用合格, 0 < theIndex < m_iSize
    if (theIndex < 0 || theIndex >= m_iSize) {
        stringstream s;
        s << "Invalid Argument : index = " << theIndex << " size = " << m_iSize << endl;
        throw invalid_argument(s.str());
    }
}

template <class T>
bool circularListWithHeader<T>::empty() const { 
    return m_iSize == 0; 
}

template <class T>
int circularListWithHeader<T>::size() const { 
    return m_iSize; 
}

template <class T>
T& circularListWithHeader<T>::get(int theIndex) const { //返回索引为theIndex的元素
    checkIndex(theIndex);
    circularListNode<T> *currentNode = firstNode->next;
    for (int i = 0; i < theIndex; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

template <class T>
int circularListWithHeader<T>::indexOf(const T &theElement) const { //返回元素theElement第一次出现时的索引
	// 让头结点来存放要查找的元素，从首节点开始进行查找，如果最终找到的位置是在头结点，说明链表中不存在该元素
    firstNode->element = theElement;
    int index = 0;
    circularListNode<T> *currentNode = firstNode->next;
    while (currentNode->element != theElement) {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == firstNode) {
        //firstNode->element = NULL;
        return -1;
    }
    else {
        //firstNode->element = NULL;
        return index;
    }
}

template <class T>
void circularListWithHeader<T>::erase(int theIndex) {    //删除索引为theIndex的元素
    checkIndex(theIndex);
    circularListNode<T> *currentNode = firstNode;    //删除首节点也不用特殊处理
    for (int i = 0; i < theIndex; i++) { //找到要删除的结点的前一个结点
        currentNode = currentNode->next;
    }
    circularListNode<T> *deleteNode = currentNode->next;
    currentNode->next = deleteNode->next;
    deleteNode->next->previous = deleteNode->previous;
    delete deleteNode;
    m_iSize--;
}

template <class T>
void circularListWithHeader<T>::insert(int theIndex, const T &theElement) { //把theElement插入线性表中索引为theIndex的位置上
    if (theIndex < 0 || theIndex > m_iSize) {
        stringstream s;
        s << "Invalid Argument : index = " << theIndex << " size = " << m_iSize << endl;
        throw invalid_argument(s.str());
    }
    circularListNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++) { //找到要删除的结点的前一个结点
        currentNode = currentNode->next;
    }
    circularListNode<T> *newNode = new circularListNode<T>(theElement);
    newNode->previous = currentNode;
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    newNode->next->previous = newNode;
    m_iSize++;
}

template <class T>
void circularListWithHeader<T>::output(ostream &out) const { //把线性表插入到输出流
    for (circularListNode<T> *currentNode = firstNode->next; currentNode != firstNode; currentNode = currentNode->next) {
        out << currentNode->element << " ";
    }
}

template <class T>
ostream& operator<<(ostream& out, const circularListWithHeader<T> theList) {
    theList.output(out);
    return out;
}
#endif // !circularListWithHeader_

