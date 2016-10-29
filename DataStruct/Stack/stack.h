/*! Author: qwchen
 *! Date: 2016-9-18
 * 栈Stack的ADT
 */

#ifndef stack_
#define stack_

using namespace std;

template <class T>
class stack {
public:
    virtual ~stack() {}
    virtual bool empty() const = 0;          // 当栈为空时返回true
    virtual int size() const = 0;            // 返回栈中元素的个数
    virtual T& top() const = 0;              // 返回栈顶元素的引用
    virtual void pop() = 0;                  // 删除栈顶元素
    virtual void push(const T& theElem) = 0; // 将元素theElem压入栈顶
};

#endif // !stack_