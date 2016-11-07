### 1 图的表示
典型图表示的性能复杂度  

|数据结构|所需空间|添加一条边v-w|检测w和v是否相邻|遍历v的所有相邻顶点|
|:---:|:---:|:---:|:---:|:---:|
|邻接矩阵|V<sup>2</sup>|1|1|V|
|邻接链表|V+E|1|degree(v)|degree(v)|
|邻接数组|V+E|1|degree(v)|degree(v)|
- 邻接矩阵表示法通常因为所需要的存储空间过大而无法使用
- 邻接链表表示法和邻接数组表示法都是邻接表表示法。增加边时，对于邻接链表是在链表头插入节点，对于邻接数组是在数组尾部插入节点，时间复杂度都为O(1)。检测节点是否相邻和遍历节点的相邻节点时，对于邻接链表和邻接数组都是遍历该节点邻接链表和邻接数组，时间复杂度都等于该节点的度数。然而，相比链表需要指针项的存储空间和访问链表时是随机访问，数组更节省空间，并且数组的顺序存储使得访问性能更高，因此相比邻接链表，邻接数组有更大的优势。
- 下面所有的数据结构都是使用邻接数组来表示图。


### 2 无向图
1. [邻接数组表示的无向图](./Graph.h)
2. 无向图的应用
 - [单点连通性](../../Algorithms/graph/DepthFirstSearch.cpp) （深度优先搜索）
 - [单点路径](../../Algorithms/graph/DepthFirstPaths.cpp) （深度优先搜索）
 - [单点最短路径](../../Algorithms/graph/BreadthFirstPaths.cpp) （广度优先搜索）
 - [连通性](../../Algorithms/graph/ConnectedComponent.cpp) （深度优先搜索）
 - [检测环](../../Algorithms/graph/Cycle.cpp) （深度优先搜索树）
 - [双色问题（二分图）](../../Algorithms/graph/TwoColor.cpp) （深度优先搜索）
 - 符号图：符号图只需要在普通的图的基础上加上两个字典，分别是“顶点id到顶点名的映射”和“顶点名到顶点id的映射”  

### 3 有向图
1. [邻接数组表示的有向图](./Digraph.h)
2. 有向图的应用
 - 单点和多点的可达性（与无向图的[单点连通性](../../Algorithms/graph/DepthFirstSearch.cpp)问题相似，参考该问题）  
 - 单点有向路径（与无向图的[单点路径](../../Algorithms/graph/DepthFirstPaths.cpp)问题相似，参考该问题）  
 - 单点最短路径（与无向图的[单点最短路径](../../Algorithms/graph/BreadthFirstPaths.cpp)问题相似，参考该问题）
 - [有向环检测](../../Algorithms/graph/DirectedCycle.cpp) (深度优先搜索)
 - [深度优先的顶点排序](../../Algorithms/graph/DepthFirstOrder.cpp) （深度优先搜索）
 - [优先级限制下的调度问题（及 拓扑排序）](../../Algorithms/graph/topologicalOrder.cpp) （贪心算法）
 - [强连通性 Kosaraju算法](../../Algorithms/graph/Kosaraju.cpp) （深度优先搜索）


### 4 加权无向图
1. [邻接数组表示的加权有向图](./EdgeWeightedGraph.h)
2. 加权无向图的应用
 - [最小生成树（Prim算法）](../../Algorithms/graph/PrimMST.cpp)
 - [最小生成树（Kruskal算法）](../../Algorithms/graph/KruskalMST.cpp)
Prim算法和Kruskal算法不能应用于加权有向图，不可能。加权有向图的最小生成树是一个叫做最小树形图的问题。

### 5 加权有向图




