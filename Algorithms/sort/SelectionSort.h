/*！
 * 选择排序
 */

#ifndef SelectionSort_
#define SelectionSort_

#include <vector>

using namespace std;

template <class T>
class SelectionSort{
public:
    static void selectionSort(vector<T> &a, int n){
        for (int i = 0; i < n; i++){
            int min = i;
            for (int j = i+1; j < n; j++){
                if(a[j] < a[min]){
                    min = j;
                }
            }
            swap(a[i], a[min]);
        }
    }
};

#endif


