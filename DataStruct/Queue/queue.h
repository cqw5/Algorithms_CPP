/*! Author: qwchen
 *! Date: 2016-9-20
 * 队列的抽象数据类型
 */

#ifndef queue_
#define queue_

using namespace std;

template <class T>
class queue {
public:
    virtual ~queue() {}
    virtual bool empty() const = 0;           // 当队列为空时，返回true
    virtual int size() const = 0;             // 返回队列中元素的个数
    virtual T& front() = 0;                   // 返回头元素的引用
    virtual T& back() = 0;                    // 返回尾元素的引用
    virtual void pop() = 0;                   // 删除首元素
    virtual void push(const T &theElem) = 0;  // 把元素theElem加入队尾
};

#endif // !queue_
