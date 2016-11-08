/*! Author: qwchen
 *! Date  : 2016-10-20
 * 
 * 求一组数中的最大值和最小值(递归解法)
 * 思路：用递归的分治算法可以求解
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 * 递归函数
 * Parament:
 *     a: 待查找的数组
 *     low: 第一个元素
 *     high: 最后一个元素的下一个位置
 *     indexOfMin: 最小元素的索引
 *     indexOfMax: 最大元素的索引
 * return:
 *     通过形参数传引用的方式返回indexOfMin和indexOfMax
 */
template <class T>
void findMinmax(vector<T> a, int low, int high, int &indexOfMin, int &indexOfMax) {
    if (high - low == 1){ // 递归终止条件：只有一个元素时，该元素既为最小又为最大
        indexOfMin = low;
        indexOfMax = low;
        return;
    } 
    if (high - low == 2){ // 递归终止条件：有两个元素时，一个是最大，另一个是最小
        if (a[low] < a[high - 1]){
            indexOfMin = low;
            indexOfMax = high - 1;
        } else {
            indexOfMin = high - 1;
            indexOfMax = low;
        }
        return;
    }
    // 父节点的最大元素是左子树和右子树中最大元素的大者，最小元素为左子树和右子树中最小元素的小者
    int mid = (low + high) / 2;
    int indexOfLeftMin = low, indexOfLeftMax = low;
    int indexOfRightMin = mid, indexOfRightMax = mid;
    findMinmax(a, low, mid, indexOfLeftMin, indexOfLeftMax);
    findMinmax(a, mid, high, indexOfRightMin, indexOfRightMax);
    indexOfMin = a[indexOfLeftMin] <= a[indexOfRightMin]? indexOfLeftMin : indexOfRightMin;
    indexOfMax = a[indexOfLeftMax] >= a[indexOfRightMax]? indexOfLeftMax : indexOfRightMax;
}

/*
 * Parament:
 *     a: 待查找的数组
 *     n: 数组元素的个数(即最后一个元素的下一个位置)
 *     indexOfMin: 最小元素的索引
 *     indexOfMax: 最大元素的索引
 * return:
 *     通过形参传引用的方式返回indexOfMin和indexOfMax
 */
template <class T>
bool minmax(vector<T> a, int n, int &indexOfMin, int &indexOfMax) {
    if (n < 1){ // 如果数组为空，返回false
        return false;
    }
    findMinmax(a, 0, n, indexOfMin, indexOfMax);
    return true;
}

testMinmax(){
    // index         0  1  2  3  4  5  6  7  8  9  10 11 
    vector<int> a = {9, 2, 4, 6, 2, 1, 7, 5, 9, 10, 3, 3};
    vector<int> b;
    int min = 0;
    int max = 0;
    if(minmax(a, a.size(), min, max)) {
        cout << "min = " << a[min] << "  it's index = " << min << endl;
        cout << "max = " << a[max] << "  it's index = " << max << endl;
    } else {
        cout << "Error" << endl;
    }
}

int main(){
    testMinmax();
    return 0;
}

