/*！
 *  迭代实现的归并排序
 */

#ifndef MergeSortIteration_
#define MergeSortIteration_

#include <vector>

using namespace std;

template <class T>
class MergeSortIteration{
public:
    static void mergeSort(vector<T> &a, int n);  // 归并排序
private:
    static void mergePass(vector<T> &a, vector<T> &b, int n, int segmentSize);  // 从a到b 归并相邻的数据段
    static void merge(vector<T> &a, vector<T> &b, int low, int mid, int high);  // 将a[low ... mid]和a[mid+1 ... high]归并到a[low ... high]
};

template <class T>
void MergeSortIteration<T>::mergeSort(vector<T> &a, int n){
    vector<T> b(n);
    int segmentSize = 1;
    while(segmentSize < n){
        mergePass(a, b, n, segmentSize);
        segmentSize += segmentSize;
        mergePass(b, a, n, segmentSize);
        segmentSize += segmentSize;
    }
}

template <class T>
void MergeSortIteration<T>::mergePass(vector<T> &a, vector<T> &b, int n, int segmentSize){
    int i = 0;
    for (; i + 2 * segmentSize <= n; i += 2 * segmentSize){
        merge(a, b, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
    }
    // 少于两段的数据
    if (i + segmentSize < n){  // 剩有两段的数据
        merge(a, b, i, i + segmentSize - 1, n - 1);
    } else {  // 只剩下一段的数据
        for (int j = i; j < n; j++){
            b[j] = a[j];
        }
    }
}

template <class T>
void MergeSortIteration<T>::merge(vector<T> &a, vector<T> &b, int low, int mid, int high){
    int i = low;
    int j = mid + 1;
    int k = low;
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
}

#endif
