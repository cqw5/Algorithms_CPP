/*! Author: qwchen
 *! Date: 2016-9-13
 * 线性表的ADT
 */

#ifndef linearList_
#define linearList_

#include <iostream>

using namespace std;

template <class T>
class linearList {
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;                              // 返回当线性表为空时，返回true
    virtual int size() const = 0;                                // 返回线性表元素的个数
    virtual int capacity() const = 0;                            // 返回线性表的容量
    virtual T& get(int theIndex) const = 0;                      // 返回索引为theIndex的元素
    virtual int indexOf(const T &theElement) const = 0;          // 返回元素theElement第一次出现时的索引
    virtual void erase(int theIndex) = 0;                        // 删除索引为theIndex的元素
    virtual void insert(int theIndex, const T &theElement) = 0;  // 把theElement插入线性表中索引为theIndex的位置上
    virtual void output(ostream &out) const = 0;                 // 把线性表插入到输出流
};

#endif

