/*! Author: qwchen
 *! Date: 2016-11-6
 * 二分查找
 * 从序列a中查找待查找元素x的下标，
 *     若查找成功，返回下标
 *     若查找时失败，返回-1
 */

#ifndef binarySearch_
#define binarySearch_

#include <iostream>

using namespace std;

/*
 * Parament:
 *     a：序列
 *     n：序列a的长度
 *     x：待查找元素
 * Return：
 *     待查找元素的下标，不存在时返回-1
 */
template <class T>
int binarySearch(T *a, int n, const T &x) {
    int low = 0, high = n - 1;
    int mid = 0;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < a[mid])      high = mid - 1;
        else if (x > a[mid]) low = mid + 1;
        else                 return mid;
    }
    return -1;
}

#endif