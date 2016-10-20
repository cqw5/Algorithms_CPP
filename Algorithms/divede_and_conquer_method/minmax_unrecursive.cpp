/*！
 * 求一组数中的最大值和最小值(非递归解法)
 * 
 */

#include <iostream>
#include <vector>

using namespace std;

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
bool minmax(vector<T> a, int n, int &indexOfMin, int &indexOfMax){
	// 如果数组为空，返回false
    if (n < 1){
        return false;
    }
    if (n == 1){
        indexOfMin = indexOfMax = 0;
        return true;
    }
    int s = 1;
    if (n % 2) { // 元素个数是奇数
        indexOfMin = indexOfMax = 0;
    } else {     // 元素个数是偶数
        if (a[0] < a[1]){
            indexOfMin = 0;
            indexOfMax = 1;
        } else {
            indexOfMin = 1;
            indexOfMax = 0;
        }
        s = 2;
    }
    // 比较剩余的元素对
    for (; s + 2 <= n; s = s + 2){
        if (a[s] < a[s + 1]){
            if (a[s] < a[indexOfMin]) {
                indexOfMin = s;
            }
            if (a[s + 1] > a[indexOfMax]) {
                indexOfMax = s + 1;
            }
        } else {
            if (a[s + 1] < a[indexOfMin]) {
                indexOfMin = s + 1;
            }
            if (a[s] > a[indexOfMax]) {
                indexOfMax = s;
            }
        }
    }
    return true;
}

void testMinmax(){
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