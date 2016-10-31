/*! Author: qwchen
 *! Date: 2016-9-24
 * 
 * 链式散列的哈希表
 */

#ifndef hashChain_
#define hashChain_

#include <iostream>
#include "dictionary.h"
#include "sortedChain.h"

using namespace std;

template <class K, class E>
class hashChain :public dictionary<K, E> {
public:
    hashChain(int theDivisor = 11);
    ~hashChain();
    bool empty() const;                      // 当散列表为空时，返回true
    int size() const;                        // 返回散列表中数对的数目
    pair<const K, E>* find(const K&) const;  // 返回匹配数对的指针
    void erase(const K&);                    // 删除匹配的数对
    void insert(const pair<const K, E>&);    // 往散列表中插入一个数对
    void output(ostream& out) const;
private:
    sortedChain<K, E>* table;   // 散列表
    int dSize;                  // 散列表元素的个数
    int diviosr;                // 除数      
    hash<K> hash;               // 哈希函数
};

template <class K, class E>
hashChain<K, E>::hashChain(int theDivisor) {
    if (theDivisor <= 0) {
        stringstream s;
        s << "Divisor must be > 0" << endl;
        throw invalid_argument(s.str());
    }
    diviosr = theDivisor;
    table = new sortedChain<K, E>[diviosr];
    dSize = 0;
}

template <class K, class E>
hashChain<K, E>::~hashChain(){
    delete []table;
}

template <class K, class E>
bool hashChain<K, E>::empty() const {
    return dSize == 0;
}

template <class K, class E>
int hashChain<K, E>::size() const {
    return dSize;
}

template <class K, class E>
pair<const K, E>* hashChain<K, E>::find(const K& theKey) const {
    int d = (int)hash(theKey) % diviosr;
    return table[d].find(theKey);
}

template <class K, class E>
void hashChain<K, E>::insert(const pair<const K, E>& thePair) {
    int d = (int)hash(thePair.first) % diviosr;
    int oldSize = table[d].size();
    table[d].insert(thePair);
    int newSize = table[d].size();
    if (newSize > oldSize)
        dSize++;
}

template <class K, class E>
void hashChain<K, E>::erase(const K& theKey) {
    int d = (int)hash(theKey) % diviosr;
    int oldSize = table[d].size();
    table[d].erase(theKey);
    int newSize = table[d].size();
    if (newSize < oldSize)
        dSize--;
}

template <class K, class E>
void hashChain<K, E>::output(ostream& out) const {
    for (int i = 0; i < diviosr; i++) {
        out << "Bucket " << i << " : ";
        if (table[i].size() == 0)
            out << "NULL" << endl;
        else
            out << table[i] << endl;
    }
}

template <class K, class E>
ostream& operator<<(ostream &out, hashChain<K, E> table) {
    table.output(out);
    return out;
}

#endif // !hashChain_
