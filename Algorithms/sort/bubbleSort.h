/*! Author: qwchen
 *! Date: 2016-10-23
 * 冒泡排序
 */

#ifndef BubbleSort_
#define BubbleSort_

#include <vector>

using namespace std;

template <class T>
class BubbleSort{
public:
    // 冒泡排序标准版本
    static void bubbleSort(vector<T> &a, int n){
        for (int i = n; i > 1; i--){  // 进行n-1趟冒泡
            for (int j = 0; j < i-1; j++){  // 每一趟冒泡，选取前i个元素中最大的元素放到第i个位置
                if (a[j] > a[j+1]){
                    swap(a[j], a[j+1]);
                }
            }
        }
    }
    // 冒泡排序提前终止版本
    static void bubbleSortEarlyStop(vector<T> &a, int n){
        bool sorted = false;
        for (int i = n; i > 1; i--){  // 进行n-1趟冒泡
            sorted = true;  // 排序开始时假定已经有序
            for (int j = 0; j < i-1; j++){  // 每一趟冒泡，选取前i个元素中最大的元素放到第i个位置
                if (a[j] > a[j+1]){
                    sorted = false;  // 如果无序，将sorted改为false
                    swap(a[j], a[j+1]);
                }
            }
            if (sorted) return;  // 一个一趟排序，元素位置都没有交换，说明已经有序，提前停止算法
        }
    }
};

#endif
