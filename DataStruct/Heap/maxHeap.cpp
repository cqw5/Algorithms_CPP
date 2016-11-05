/*! Author: qwchen
 *! Date: 2016-9-28
 * 测试用数组实现的大顶堆
 */

#include <iostream>
#include "maxHeap.h"

using namespace std;

void testMaxHeap() {
    maxHeap<int> h(4);
    h.push(10);
    h.push(20);
    h.push(5);
    cout << "Heap size is " << h.size() << endl;
    cout << "Element in array order are : ";
    cout << h << endl;

    h.push(15);
    h.push(30);
    cout << "Heap size is " << h.size() << endl;
    cout << "Element in array order are : ";
    cout << h << endl;

    cout << "The max element is " << h.top() << endl;
    h.pop();
    cout << "The max element is " << h.top() << endl;
    h.pop();
    cout << "The max element is " << h.top() << endl;
    h.pop();
    cout << "Heap size is " << h.size() << endl;
    cout << "Element in array order are : ";
    cout << h << endl;

    int z[10];
    z[0] = 0;
    for (int i = 1; i < 10; i++) {
        z[i] = i;
    }
    h.initialize(z, 9);
    cout << "Elements in array order are : ";
    cout << h << endl;
}

int main(){
    testMaxHeap();
    return 0;
}