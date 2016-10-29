/*! Author: qwchen
 *! Date: 2016-10-23
 * 快速排序
 */

#ifndef QuickSort_
#define QuickSort_

#include <vector>

using namespace std;

template <class T>
class QuickSort{
public:
    static void quickSort(vector<T> &a, int n);
private:
    static void sort(vector<T> &a, int low, int high);
    static int partition(vector<T> &a, int low, int high);  // 将数组切分为a[low, mid-1], a[mid], a[mid+1]
};

template <class T>
void QuickSort<T>::quickSort(vector<T> &a, int n){
    sort(a, 0, n - 1);
}

template <class T>
void QuickSort<T>::sort(vector<T> &a, int low, int high){
    if (low >= high) return;
    int mid = partition(a, low, high);  // 切分
    sort(a, low, mid - 1);              // 将左半部分排序
    sort(a, mid + 1, high);             // 将右半部分排序
}

template <class T>
int QuickSort<T>::partition(vector<T> &a, int low, int high){
    T key = a[low];
    while(low < high){
        while(low < high && key <= a[high]) high--;  // 注意是key <= a[high]，而不是key < a[high]，否则陷入死循环
        a[low] = a[high];
        while(low < high && key >= a[low]) low++;
        a[high] = a[low];
    }
    a[low] = key;
    return low;
}

#endif

