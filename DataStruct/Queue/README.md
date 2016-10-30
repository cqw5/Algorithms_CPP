###队列的数组实现和队列的链表实现
 - 数组实现
   1. 数组实现的队列是一个带头结点的循环队列，其中front指针指向头结点，back指针指向最后一个结点
   2. 对于循环队列：
    - 第i个元素的位置：location(i) = (location(队列首元素)+i)%数组长度
    - 队列为空条件是：front = back
    - 队列为满的条件是：(back+1)%数组长度 = front
 - 链表实现
   1. 链表实现的队列，其中front指针指向首节点（没有头结点），back指针指向最后一个结点
   2. 从链表头删除元素，从链表尾增加元素

###STL中的队列
 - [queue](http://www.cplusplus.com/reference/queue/queue/?kw=queue)：基于数组实现

###代码实现
 - [队列的抽象数据类型](./queue.h)
 - [数组实现的队列](./arrayQueue.h)
 - [链表实现的队列](./linkedQueue.h)

###队列的应用
 - [列出车厢从排列](../../Algorithms/queue/railroadReSort.cpp)
 - [寻找迷宫中两点的最短路径](../../Algorithms/queue/findShortPath.cpp)




