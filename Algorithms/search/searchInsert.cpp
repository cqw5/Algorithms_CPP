/*! Author: qwchen
 *! Date: 2016-12-10
 *  二分查找
 *  从序列a中查找待查找元素target的下标，
 *      若查找成功，返回下标
 *      若查找时失败，返回元素target插入的位置(注意到查找失败是，low指针会指向第一个大于target的元素，该元素的位置就是target的插入位置)
 */

#include <iostream>
#include <vector>

using namespace std;

template<class T>
int searchInsert(vector<T>& a, const T target) {
    int low = 0;
    int high = a.size() - 1;
    int mid = 0;
    while (low <= high) {
        mid = (low + high) / 2;
        if (target < a[mid])      high = mid - 1;
        else if (target > a[mid]) low = mid + 1;
        else                      return mid;
    }
    return low;
}

void test() {
    vector<int> a = {1,3,5,6};
    cout << searchInsert(a, 5) << endl;  // 2
    cout << searchInsert(a, 2) << endl;  // 1
}

int main() {
    test();
    return 0;
}

