/*!
 * 测试和比较各种排序算 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "bubbleSort.h"

#define random(x) (rand() % x)

using namespace std;


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
 * Parament:
 *     n: 排序元素的个数
 *     range：排序元素的范围
 */ 
void testSort(int n, int range){
	cout << "Element number: " << n << ", range:[0," << range << "): " << endl; 
	vector<int> a = genData(n, range);
	printTime(BubbleSort<int>::bubbleSort, "BubbleSort", a);                    // 冒泡(标准版)
	printTime(BubbleSort<int>::bubbleSortEarlyStop, "bubbleSortEarlyStop", a);  // 冒泡(提取终止版)
}

int main(){
	testSort(10000, 100000);
	return 0;
}