/*! Author: qwchen
 *! Date: 2016-9-24
 * 
 * 线性探测的哈希表
 */

#ifndef hashTable_
#define hashTable_

#include <sstream>
#include <iostream>

using namespace std;

template <class K, class E>
class hashTable {
public:
    hashTable(int theDivisor = 11);
    ~hashTable();
    bool empty() const;                      // 当字典为空时，返回true
    int size() const;                        // 返回字典中数对的数目
    pair<const K, E>* find(const K&) const;  // 返回匹配数对的指针
    void insert(const pair<const K, E>&);    // 往字典中插入一个数对
    void erase(const K&) {}                  // 删除匹配的数对(没有实现)
    void output(ostream &out) const;

private:
    int search(const K&) const;
    pair<const K, E> **table;  // 哈希表
    int dSize;                 // 元素个数
    int diviosr;               // 桶的个数
    hash<K> hash;              // STL的哈希函数 
};

template <class K, class E>
hashTable<K, E>::hashTable(int theDivisor) {
    if (theDivisor <= 0) {
        stringstream s;
        s << "Divisor must be > 0" << endl;
        throw invalid_argument(s.str());
    }
    dSize = 0;
    diviosr = theDivisor;
    table = new pair<const K, E>*[diviosr];
    for (int i = 0; i < diviosr; i++) {
        table[i] = NULL;
    }
}

template <class K, class E>
hashTable<K, E>::~hashTable() { 
    delete []table; 
}

template <class K, class E>
bool hashTable<K, E>::empty() const {
    return dSize == 0;
}

template <class K, class E>
int hashTable<K, E>::size() const {
    return dSize;
}

template <class K, class E>
int hashTable<K, E>::search(const K& theKey) const {
    int i = (int)hash(theKey) % diviosr;
    int j = i;
    do {
        if (table[j] == NULL || table[j]->first == theKey)    // 找到为NULL或者找到确定值
            return j;
        j = (j + 1) % diviosr;
    } while (i == j);
    return j;    // 散列表满
}

template <class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const {
    int i = search(theKey);
    if (table[i] == NULL || table[i]->first != theKey)    // 找不到或者散列表满
        return NULL;
    return table[i];    // 找到了
}

template <class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair) {
    int i = search(thePair.first);
    if (table[i] == NULL) {    // 找不到，即NULL，直接插入
        table[i] = new pair<const K, E>(thePair);
        dSize++;
    }
    else {
        if (table[i]->first == thePair.first) {    // 找到了，替换
            table[i]->second = thePair.second;
        }
        else {    // 散列表满，抛异常
            stringstream s;
            s << "hashTable have already full." << endl;
            throw range_error(s.str());
        }
    }
}

template <class K, class E>
void hashTable<K, E>::output(ostream& out) const {
    for (int i = 0; i < diviosr; i++) {
        if (table[i] == NULL)
            cout << "NULL" << endl;
        else
            cout << table[i]->first << " : " << table[i]->second << endl;
    }
}

template <class K, class E>
ostream& operator<<(ostream &out, const hashTable<K, E> &x) {
    x.output(out);
    return out;
}
#endif // !hashTable_




