/*! Author: qwchen
 *! Date  : 2016-11-21
 * 从数组(未排序)中查找第k小的元素，数组元素可能有重复，也可能没有。
 * 思想：借鉴三向切分快速排序的思想，用上向切分的方法将数组切为三个部分：小于key、等于key、大于key
 *       如果k在等于key的范围内，则key就是第k小元素；如果k在小于key的范围内，递归从小于key中寻找k；如果k在大于key的范围内，递归从大于key中寻找k
 * 时间复杂度：O(n)
 * 空间复杂度：O(logn)，递归栈的大小
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * 从数组a[low: high]中查找第k个元素，k下标从0开始
 */
int kthSmallest(vector<int>& a, int low, int high, int k) {
    if (low >= high) {
        return a[low];
    }
    int lt = low,
        mid = low + 1,
        gt = high;
    int key = a[low];
    while (mid <= gt) {
        if (a[mid] > key) {
            swap(a[mid], a[gt--]);
        }
        else if (a[mid] < key) {
            swap(a[mid++], a[lt++]);
        }
        else { // a[mid] == key
            mid++;
        }
    }
    if (k < lt) {
        return kthSmallest(a, low, lt-1, k);
    }
    else if (k > gt) {
        return kthSmallest(a, gt+1, high, k);
    }
    else {
        return a[k];
    }
}

void test(){
    vector<int> a = {1,3,5,2,3,5,1,4,6,6};
    int k = 6;
    int kSmall = kthSmallest(a, 0, a.size()-1, k-1); // k的下标从0开始，此处让k-1
    sort(a.begin(), a.end());
    for (int i: a) {
        cout << i << " ";
    }
    cout << endl << "the " << k << " small is " << kSmall << endl;
}

int main() {
    test();
    return 0;
}

