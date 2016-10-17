/*!
 * 组合公式：C(n,r):从n个数中取r个数的组合。如对于n=4个数{1,2,3,4}，r=2，则打印：{1,2} {1,3} {1,4} {2,3} {2,4} {3,4}。
 * 根据组合数的递归关系：C(n,r) = C(n-1,r-1) + C(n-1,r)，下面利用递归来求解该问题
 */

# include <iostream>
# include <vector>

using namespace std;

/*
 * arr是原始存储所有元素的数组
 * data是保存当前组合结果的数组
 * start, end是原始数组中未被选择的剩余数组中元素的起始位置和终止位置
 * index是已经找到的组合数的个数
 * r是总共需要的组合数的个数
 */
template <class T>
void combination(T arr, T &data, int start, int end, int index, int r){
    // 组合够r个就打印，并返回
    if(index == r){
        for(int i = 0; i < r; i++)
            cout << data[i] << " ";
        cout << endl;
        return;
    }
    // 如果剩下的数组不够(r-index)个就直接返回。 
    else if (end - start < r - index){ 
        return;
    }
    // 否则利用组合数的递归关系递归
    else {
        data[index] = arr[start]; // 记录当前数据
        combination(arr, data, start + 1, end, index + 1, r);
        combination(arr, data, start + 1, end, index, r);
    }
}

void testCombination() {
    vector<int> arr = {1, 2, 3, 4};
    int r = 2;
    vector<int> data(r);
    combination(arr, data, 0, arr.size(), 0, r);
}

int main() {
    testCombination();
    return 0;
}