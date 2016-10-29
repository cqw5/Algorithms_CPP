/*! Author: qwchen
 *! Date: 2016-10-29
 * 箱子排序
 */

#ifndef binSort_
#define binSort_

#include <vector>

using namespace std;

template <class T>
class BinSort {
public:
	static void binSort(vector<T> &a, int n, int low, int high){ // range是a中数据的范围
		vector<T> *bin = new vector<T>[high - low + 1];
		for (int i = 0; i < n; i++) {
			bin[a[i]].push_back(a[i]); 
		}
		int i = n - 1;
		for (int j = high; j >= low; j--) {
			while (!bin[j].empty()) {
				a[i--] = bin[j].back();
				bin[j].pop_back();
			}
		}
	}
};

#endif