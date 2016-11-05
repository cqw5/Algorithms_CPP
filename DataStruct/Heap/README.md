### 1 堆的特性
 - 通常将的优先队列都是用堆来实现的
 - 一个大顶堆（小顶堆）既是大根树（小根树）也是完全二叉树
 - 在堆中执行插入和删除操作的时间复杂度都为O(logN)

### 2 堆的实现
 - [堆的抽象数据类型](./heap.h)
 - [大顶堆](./maxHeap.h)
 - [小顶堆](./minHeap.h)

### 3 C\+\+ STL的堆
 - [priority_queue](http://www.cplusplus.com/reference/queue/priority_queue/?kw=priority_queue)：基于向量来实现的大顶堆，可以自定义比较函数，因此也可以作为小顶堆。

### 4 堆的应用
 - [堆排序](../../Algorithms/sort/heapSort.h)
 - [机器调度](../../Algorithms/greedy_method/LPTSchedule.cpp)
 - 霍夫曼编码