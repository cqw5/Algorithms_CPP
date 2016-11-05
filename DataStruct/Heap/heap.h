/*! Author: qwchen
 *! Date: 2016-9-28
 * 堆的抽象数据类型
 */

#ifndef heap_
#define heap_

using namespace std;

template <class T>
class heap {
public:
    virtual ~heap() {}
    virtual bool empty() const = 0;              // 返回true当且仅当堆为空
    virtual int size() const = 0;                // 返回堆的元素个数
    virtual const T& top() = 0;                  // 返回堆顶元素的引用
    virtual void pop() = 0;                      // 删除堆顶元素
    virtual void push(const T& theElement) = 0;  // 向堆中插入元素
};

#endif // !heap_

