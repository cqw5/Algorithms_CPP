/*!
 * 希尔排序
 */

#include <vector>

using namespace std;

template <class T>
class ShellSort{
public:
    static void shellSort(vector<T> &a, int n){
    	// 构造希尔排序的间隔h
        int h = 1;
        while (h < n/3){
            h = 3 * h + 1;  // 1, 4, 13, 40, 121, 364, 1093, ...
        }
        // 插入排序
        while (h >= 1){
            for (int i = h; i < n; i++){
                for (int j = i - h; j >= 0 && a[j] > a[j + h]; j -= h){
                    swap(a[j], a[j + h]);
                }
            }
            h = h / 3;
        }
    }
};

