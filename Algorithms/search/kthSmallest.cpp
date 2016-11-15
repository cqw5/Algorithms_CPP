/*! Author: qwchen
 *! Date: 2016-11-15
 * 从排序矩阵中查找从小到大的第k个数。
 * 排序矩阵定义为：每一行递增，每一列也递增。
 * 思想：二分查找。
 *       先找出矩阵中最小的元素low和最大的元素high，计算其均值mid；
 *       计算矩阵中小于等于mid的元素的个数count：
 *           如果count < k， 即k大于中间元素，则k在矩阵[mid+1, high]的后半部分
 *           如果count >= k，即k小于等于中间元素，则k在[low, mid]的前半部分
 *       不断缩减矩阵范围，直到low == high时，矩阵中剩下的这个元素就是第k个数
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 * 查找排序矩阵中，小于等于mid的元素的个数
 */
int getLessEqual(vector<vector<int>>& matrix, int mid){
    int m = matrix.size();     // 矩阵的行数
    int n = matrix[0].size();  // 矩阵的列数
    int i = m-1, j = 0;        // matrix[m-1][0]为矩阵左下角的元素
    int count = 0;
    // 累计矩阵每一列小于等于mid的元素个数。
    while(i >= 0 && j < n){
        // 对于每一列，先从后往前寻找到第一个小于等于mid的元素
        // 然后将该列中小于等于mid的元素的个数累计到count中
        if (matrix[i][j] > mid) {
            i--;
        }
        else {
            count += i + 1;
            j++;
        }
    }
    return count;
}

/*
 * 从排序矩阵中查找从小到大的第k个数，返回其值
 */
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int m = matrix.size();        // 矩阵的行数
    int n = matrix[0].size();     // 矩阵的列数
    int low = matrix[0][0];       // 矩阵的最小元素
    int high  = matrix[m-1][n-1]; // 矩阵的最大元素
    while(low < high){            // 当low == high时，就剩下一个元素，该元素就是要查找的元素
        int mid = low + (high - low) / 2;       
        int count = getLessEqual(matrix, mid); //查找“小于等于”mid的元素的个数
        // 没有k == count 是因为如果让k == count，那么此时应该k的值为mid，但是只是low和high的均值，不一定存在于矩阵中。
        if (k > count) low = mid + 1;  // k > count，即k大于中间元素，则k在[mid+1, high]的后半部分
        else           high = mid;     // k <= count，即k小于等于中间元素，则k在[low, mid]的前半部分
    }
    return low;
}


void testSearch(){
    vector<vector<int>> matrix = {
        {1, 5, 7},
        {3, 7, 8},
        {4, 8, 9}
    };
    cout << kthSmallest(matrix, 4) << endl;  // 5
}

int main(){
    testSearch();
}

