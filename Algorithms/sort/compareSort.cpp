/*!
 * 测试和比较各种排序算 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "bubbleSort.h"
#include "selectionSort.h"
#include "insertSort.h"
#include "shellSort.h"
#include "mergeSortRecursion.h"
#include "mergeSortIteration.h"
#include "quickSort.h"
#include "quickSort3Way.h"
#include "heapSort.h"

#define random(x) (rand() % x)

using namespace std;

/*
 * 产生num个范围在[0, range)内的数，将数保存为一个vector返回
 */
vector<int> genData(const int num, const int range){
    vector<int> a;
    for (int i = 0; i < num; i++){
        a.push_back(random(range));
    }
    return a;
}

/*
 * 打印算法的执行时间
 * Parament:
 *     void(*sort)(vector<int>&, int): 指针函数，指向排序算法
 *     name: 排序算法的名称
 *     a: 待排序的数组
 */
void printTime(void(*sort)(vector<int>&, int), string name, vector<int> a){
    clock_t start_time, end_time;    // 时间，单位毫秒ms
    int duration;                    // 程序执行时间，单位毫秒ms
    start_time = clock();
    sort(a, a.size());
    end_time = clock();
    duration = end_time - start_time;
    cout << name << ": " << duration << "ms" << endl;
}

/*
 * 比较排序算法的执行时间
 * Parament:
 *     n: 排序元素的个数
 *     range：排序元素的范围
 */ 
void compareByTime(int n, int range){
    cout << "Element number: " << n << ", range:[0," << range << "): " << endl; 
    vector<int> a = genData(n, range);
    printTime(BubbleSort<int>::bubbleSort, "BubbleSort", a);                    // 冒泡(标准版)
    printTime(BubbleSort<int>::bubbleSortEarlyStop, "BubbleSortEarlyStop", a);  // 冒泡(提取终止版)
    printTime(SelectionSort<int>::selectionSort, "SelectionSort", a);           // 选择排序
    printTime(InsertSort<int>::insertSort, "InsertSort", a);                    // 插入排序
    printTime(ShellSort<int>::shellSort, "ShellSort", a);                       // 希尔排序
    printTime(MergeSortRecursion<int>::mergeSort, "MergeSortRecursion", a);     // 归并排序(递归)
    printTime(MergeSortIteration<int>::mergeSort, "MergeSortIteration", a);     // 归并排序(迭代)
    printTime(QuickSort<int>::quickSort, "QuickSort", a);                       // 快速排序
    printTime(QuickSort3Way<int>::quickSort, "QuickSort3Way", a);               // 三向切分快速排序
    printTime(HeapSort<int>::heapSort, "HeapSort", a);                          // 堆排序
}


/*
 * 打印排序完的结果
 */
void printSorted(void(*sort)(vector<int>&, int), string name, vector<int> a){
    sort(a, a.size());
    cout << name << ": ";
    for (int elem: a){
        cout << elem << " ";
    }
    cout << endl;
}

/*
 * 测试排序算法的正确性
 */
void testSort(int n, int range){
    vector<int> a = genData(n, range);
    cout << "Original Array: ";
    for (int elem: a){
        cout << elem << " ";
    }
    cout << endl;
    printSorted(BubbleSort<int>::bubbleSort, "BubbleSort", a);                    // 冒泡(标准版)
    printSorted(BubbleSort<int>::bubbleSortEarlyStop, "bubbleSortEarlyStop", a);  // 冒泡(提取终止版)
    printSorted(SelectionSort<int>::selectionSort, "SelectionSort", a);           // 选择排序
    printSorted(InsertSort<int>::insertSort, "InsertSort", a);                    // 插入排序
    printSorted(ShellSort<int>::shellSort, "ShellSort", a);                       // 希尔排序
    printSorted(MergeSortRecursion<int>::mergeSort, "MergeSortRecursion", a);     // 归并排序(递归)
    printSorted(MergeSortIteration<int>::mergeSort, "MergeSortIteration", a);     // 归并排序(迭代)
    printSorted(QuickSort<int>::quickSort, "QuickSort", a);                       // 快速排序
    printSorted(QuickSort3Way<int>::quickSort, "QuickSort3Way", a);               // 三向切分快速排序
    printSorted(HeapSort<int>::heapSort, "HeapSort", a);                          // 堆排序
}

int main(){
    cout << "----------------------- testSort -----------------------" << endl;
    testSort(10, 100);
    cout << endl;
    cout << "-------------------- compareByTime ---------------------" << endl;
    compareByTime(10000, 100000);
    cout << "------- compareByTime (have large repeat element) ------" << endl;
    compareByTime(10000, 100);
    return 0;
}