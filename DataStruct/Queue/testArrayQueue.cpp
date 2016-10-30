/*! Author: qwchen
 *! Date: 2016-9-21
 * 
 * 测试用数组实现的队列（带头结点的循环队列）
 */

#include <iostream>
#include "arrayQueue.h"

using namespace std;

void testArrayQueue() {
	arrayQueue<int> q(4);
	// test push
	q.push(1);
	cout << "Queue rear is " << q.back() << endl;
	q.push(2);
	cout << "Queue rear is " << q.back() << endl;
	q.push(3);
	cout << "Queue rear is " << q.back() << endl;
	q.push(4);
	cout << "Queue rear is " << q.back() << endl;
	cout << "Queue should be 1234, front to rear" << endl;

	// test empty
	if (q.empty()) cout << "The queue is empty" << endl;
	else           cout << "The queue is not empty" << endl;
	
	// test size
	cout << "The queue size is " << q.size() << endl;

	// test pop
	while (!q.empty()) {
		cout << "Queue front is " << q.front() << endl;
		q.pop();
		cout << "Popped front element" << endl;
	}

	try { 
		q.pop(); 
	}
	catch (exception e) {
		cout << "Last pop failed " << endl;
		cout << e.what() << endl;
	}

	// test push
	arrayQueue<int> r(4);
	r.push(1);
	r.push(2);
	r.push(3);
	r.pop();
	r.pop();
	r.push(4);
	r.push(5);
	r.push(6);
	r.push(7);
	cout << "Queue should be 34567, front to rear" << endl;
	// test empty and size
	if (r.empty()) cout << "The queue is empty" << endl;
	else           cout << "The queue is not empty" << endl;

	cout << "The queue size is " << r.size() << endl;

	while (!r.empty()) {
		cout << "Queue front is " << r.front() << endl;
		r.pop();
		cout << "Popped front element" << endl;
	}
}

int main(){
	testArrayQueue();
	return 0;
}
