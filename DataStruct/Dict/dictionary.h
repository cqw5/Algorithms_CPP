/*! Author: qwchen
 *! Date: 2016-9-24
 * 
 * 字典的抽象数据类型
 */

#ifndef dictionary_
#define dictionary_

using namespace std;

template <class K, class E>
class dictionary {
public:
    virtual ~dictionary() {}
    virtual bool empty() const = 0;                      // 当字典为空时，返回true
    virtual int size() const = 0;                        // 返回字典中数对的数目
    virtual pair<const K, E>* find(const K&) const = 0;  // 返回匹配数对的指针
    virtual void erase(const K&) = 0;                    // 删除匹配的数对
    virtual void insert(const pair<const K, E>&) = 0;    // 往字典中插入一个数对
};

#endif // !dictionary_
