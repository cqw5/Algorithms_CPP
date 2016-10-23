/*！
 *  递归实现的归并排序
 */

#ifndef MergeSortRecursion_
#define MergeSortRecursion_

#include <vector>

using namespace std;

template <class T>
class MergeSortRecursion{
public:
    static void mergeSort(vector<T> &a, int n);  // 归并排序
private:
    static void sort(vector<T> &a,  vector<T> &b, int low, int high);  // 将数组a[low ... high]排序
    static void merge(vector<T> &a,  vector<T> &b, int low, int mid, int high);  // 将a[low ... mid]和a[mid+1 ... high]归并到a[low ... high]
};

template <class T>
void MergeSortRecursion<T>::mergeSort(vector<T> &a, int n){
    vector<T> b(n);  // 给辅助数组分配空间
    sort(a, b, 0, n - 1);
}

template <class T>
void MergeSortRecursion<T>::sort(vector<T> &a, vector<T> &b, int low, int high){
    if (low >= high) return;
    int mid = (low + high) / 2;
    sort(a, b, low, mid);         // 将左半边排序
    sort(a, b, mid + 1, high);    // 将右半边排序
    merge(a, b, low, mid, high);  // 归并结果
}

template <class T>
void MergeSortRecursion<T>::merge(vector<T> &a, vector<T> &b, int low, int mid, int high){
    int i = low;       // i指向a左边数组的第一个元素
    int j = mid + 1;   // j指向a右边数组的第一个元素
    int k = low;       // k为b中的指针
    // 将a[low ... mid]和a[mid+1 ... high]归并到b[low ... high]
    while(i <= mid && j <= high){
        if (a[i] < a[j]){
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }
    while(i <= mid){
        b[k++] = a[i++];
    }
    while(j <= high){
        b[k++] = a[j++];
    }
    // 将b[low ... high] 拷贝回 a[low ... high]
    for (int i = low; i <= high; i++){
        a[i] = b[i];
    }
}

#endif