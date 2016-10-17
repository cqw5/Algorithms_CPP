/*!
 * 全排列公式A(n)：对n个数进行全排列。如对于n=3个数{1,2,3}，则打印：
 * {1,2,3} {1,3,2} {2,1,3} {2,3,1} {3,1,2} {3,2,1}
 * 根据排列数的递归关系：A(n) = n * A(n-1),下面利用递归来求解该问题 
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 * 对数组arr[k:n]进行全排列
 */
template <class T>
void permutations(T &arr, int k, int n){
    if (k + 1 == n){
        for (int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else{
        for (int i = k; i < n; i++){
            swap(arr[i], arr[k]);
            permutations(arr, k + 1, n);
            swap(arr[i], arr[k]);
        }
    }
}

void testPermutations(){
    vector<int> vec = {1,2,3};
    permutations(vec, 0, 3);
}

int main(){
    testPermutations();
    return 0;
}