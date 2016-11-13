/*! Author: qwchen
 *! Date: 2016-10-23
 * 快速排序的非递归版本
 * 使用栈来实现，而不是迭代。
 * 1. 申请一个栈，存放排序数组的起始位置和终点位置。
 * 2. 将整个数组的起始位置low和终点位置high进栈
 * 3. 出栈，对出栈的数据进行排序，查找基准数据所在最终的位置mid。
 * 4. 判断起始位置low是否小于基准位置high，如果小于则将起始位置和mid-1为终点位置进栈
 * 5. 判断基准位置low是否小于终点位置high，如果小于则将mid+1作为起始位置，high作为终点位置进栈
 * 6.判断栈是否为空，如果不为空则重复第三步，否则退出操作。
 */

#ifndef quickSortByStack_
#define quickSortByStack_

#include <vector>
#include <stack>

using namespace std;

template <class T>
class QuickSortByStack {
public:
    static void quickSort(vector<T>& a, int n);
private:
    static void sort(vector<T>& a, int low, int high);
    static int partition(vector<T>& a, int low, int high);
};

template <class T>
void QuickSortByStack<T>::quickSort(vector<T>& a, int n){
    sort(a, 0, n);
}

template <class T>
void QuickSortByStack<T>::sort(vector<T>& a, int low, int high){
    stack<int> s;
    int mid;
    if (low < high){
        s.push(low);
        s.push(high);
    }
    while(!s.empty()){
        high = s.top();
        s.pop();
        low = s.top();
        s.pop();
        mid = partition(a, low, high);
        if (low < mid - 1){
            s.push(low);
            s.push(mid - 1);
        }
        if (mid + 1 < high){
            s.push(mid + 1);
            s.push(high);
        }
    }
}

template <class T>
int QuickSortByStack<T>::partition(vector<T>& a, int low, int high){
    T key = a[low];
    while(low < high){
        while(low < high && key <= a[high]) high--;
        a[low] = a[high];
        while(low < high && key >= a[low]) low++;
        a[high] = a[low];
    }
    a[low] = key;
    return low;
}


#endif