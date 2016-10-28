/*! Author: qwchen
 *! Date: 2016-9-14
 * 测试线性表的数组描述
 */

#include <iostream>
#include "arrayList.h"

using namespace std;

void testArrayList() {
    arrayList<double> *x = new arrayList<double>(20);
    arrayList<int> y(2), z;

    // test capacity
    cout << "Capacity of x, y and z = "
        << ((linearList<double>*)x)->capacity() << ", "
        << y.capacity() << ", "
        << z.capacity() << endl;

    // test size
    cout << "Initial size of x, y and z = "
        << x->size() << ", "
        << y.size() << ", "
        << z.size() << endl;

    // test empty
    if (x->empty()) cout << "x is empty" << endl;
    else cout << "x is not empty" << endl;
    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;

    // test insert
    try{
        y.insert(0, 2);
        y.insert(1, 6);
        y.insert(0, 1);
        y.insert(2, 4);
        y.insert(3, 5);
        y.insert(2, 3);
    } catch (exception e) {
        cout << e.what() << endl;
    }
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;
    cout << endl << "Testing overload" << endl;
    cout << y << endl;

    // test indexOf
    int index = y.indexOf(4);
    if (index < 0) cout << "4 not found" << endl;
    else cout << "The index of 4 is " << index << endl;
    index = y.indexOf(7);
    if (index < 0) cout << "7 not found" << endl;
    else cout << "The index of 7 is " << index << endl;

    // test get
    cout << "Element with index 0 is " << y.get(0) << endl;
    cout << "Element with index 3 is " << y.get(3) << endl;

    // test erase
    y.erase(1);
    cout << "Element 1 erased" << endl;
    cout << "The list is " << y << endl;
    y.erase(2);
    cout << "Element 2 erased" << endl;
    cout << "The list is " << y << endl;

    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;

    try { 
        y.insert(-3, 0); 
    } catch (exception e)
    {
        cout << "Illegal index exception" << endl;
        cout << "Insert index must be between 0 and list size" << endl;
        cout << e.what() << endl;
    }

    // test copy constructor
    arrayList<int> w(y);
    y.erase(0);
    y.erase(0);
    cout << "w should be old y, new y has first 2 elements removed" << endl;
    cout << "w is " << w << endl;
    cout << "y is " << y << endl;

}

int main(){
    testArrayList();
    return 0;
}