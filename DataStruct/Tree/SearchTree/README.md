## 搜索树  

搜索树适用于描述[字典](../../Dict)（字典有两种比较好的描述，有序的字典有搜索树描述，无序的字典用散列（哈希）描述）  
搜索树的节点类型是pair<const K, E>，可通过K比较大小。  

### 1 二叉搜索树  

#### 1.1 二叉搜索树和索引二叉搜索树   
- 二叉搜索树  
  二叉搜索树是一棵二叉树，可能为空；一棵非空的二叉搜索树满足以下特征：  
  - 任意两个元素（节点）的关键字都不同。（有关键字相同的节点话，称为**有重复值的二叉搜索树**）  
  - 对于任意一个节点，其左子树（如果存在）的节点的关键字都小于该节点，其右子树（如果存在）的节点的关键字都大于该节点。  
- 索引二叉搜索树  
  索引二叉搜索树在二叉搜索树的基础上，每个节点中都添加一个leftSize域，这个域的值是该节点左子树的元素个数。  

#### 1.2 二叉搜索树的实现 
 - 二叉搜索树的元素类型是pair<const K, E>，其中K是关键字类型，E是相应的元素的数据类型。  
 - 使用中序遍历就可以完成将二叉搜索树的元素按照key从小到大输出。  
 - 搜索：pair<const K, E>\* **find**(const K &theKey)  
&emsp;&emsp;二分查找的过程。假设要查找关键字为theKey的元素。先从根节点开始查找。如果根为空，那么搜索树不包含任何元素，即查找失败。如果不为空，则将theKey与根的关键字比较。如果theKey<根节点的关键字，则查找左子树；如果theKey>根节点的关键字，则查找右子树；如果theKey=根节点的关键字，则查找成功。在子树的查找过程与此类似。  
 - 插入：void **insert**(const pair<const K, E> &thePair)  
&emsp;&emsp;假设要在二叉搜索树中插入一个新元素thePair，首先通过搜索来确定树中是否存在某个元素，其关键字与thePair.first相同。如果搜索成功，那么就用thePair.second替代该元素的值。如果搜索不成功，那么就将新元素作为搜索中断节点的孩子插入二叉搜索树中。（插入的节点一定是孩子节点）
 - 删除：void **erase**(const K &theKey)  
&emsp;&emsp;假设要删除的节点时p，有3种情况：  
   1. p是叶子节点。处理方法是释放该叶节点空间，若是根节点，则令根为NULL。
   2. p只有一棵子树。如果p没有父节点（是根节点），则p的唯一子树的根节点成为新的搜索树的根节点。如果p有父节点pp，则修改pp的指针域，使它指向p的唯一孩子，然后释放节点p。
   3. p具有两课非空子树。将该节点的元素替换为它的左子树的最大元素或右子树的最小元素，然后把替换元素的结点删除。（替换后，就转化为第1或第2中情况了）
 - 扩展功能：查找小于等于theKey的最大元素：pair<const K, E>\* **findLE**(const K& theKey)
 - 扩展功能：查找大于等于theKey的最小元素：pair<const K, E>\* **findGE**(const K& theKey)
 - 代码实现：[二叉搜索树](./binarySearchTree.h)

### 2 平衡搜索树
#### 2.1 AVL树
 - 空树T是一棵AVL树，如果树T非空，当且仅当T满足以下条件时，T是一棵AVL树：
   - T的左子树和右子树都是AVL树。
   - |h<sub>L</sub> - h<sub>R</sub>| ≤ 1，其中h<sub>L</sub>和h<sub>R</sub>分别是T的左子树和右子树的高。
 - 定义节点的平衡因子为：h<sub>L</sub> - h<sub>R</sub>，取值为：-1、0、1
   插入节点和删除节点都有时，都有保持树中每个结点平衡因子的值为：-1、0或1

#### 2.2 红黑树
 - 红黑树是这样一棵二叉搜索树：树中每一个节点的颜色或者是黑色或者是红色。
   - 红黑树的性质（通过结点描述）
     1. 根节点和所有的外部节点都是黑色。
     2. 在根节点到外部节点的路径上，没有连续两个节点时红色。
     3. 在所有根节点到外部节点的路径上，黑色节点的数目相同。
   - 红黑树的性质（通过指针描述，从父节点指向黑色孩子的指针是黑色的，从父节点指向红色孩子的指针是红色的）
     1. 从内部节点指向外部节点的指针是黑色的。
     2. 从根节点至外部节点路径上，没有两个连续的红色指针。
     3. 在所有根节点到外部节点的路径上，黑色指针的数目都相同。
 - 红黑树节点的阶：从该节点到一外部节点的路径上黑色指针的数量。
 - 最长路径和最短路径：设从根到外部节点的路径长度是该路径上指针的数量。P和Q分别表示两条从根节点到外部节点的路径，那么length(P)≤2length(Q)。（最长的路径是红黑相间的路径，最短的路径是全部为黑色节点的路径，最长路径不超过最短路径的两倍。）
 - 高度与节点数：令h是一棵红黑树的高度（不包括外部节点），n是树的内部节点数量，而r是根节点的阶，则：
   - h ≤ 2r
   - n ≥ 2<sup>r</sup> - 1
   - h ≤ 2log<sub>2</sub>(n+1)

#### 2.3 分裂树

#### 2.4 B-树
 - m阶B-树是一棵m叉搜索树。如果B-树非空，那么其满足以下条件：
   - 根节点至少有2个孩子。
   - 除了根节点外，所有内部节点至少有(m/2)上取整个孩子。
   - 所有外部节点都在同一层。

#### 2.5 AVL树、红黑树、分裂树 和 B-树 对比
 - AVL树、红黑树和分裂树适合内部存储的应用，B-树适合外部存储的应用（如 存储在磁盘上的大型词典）。
 - AVL树和红黑树都是使用“旋转”来保持平衡。AVL树对一次插入操作最多需要一次旋转，对每个删除操作最多需要logn次旋转；而红黑树对每个插入和删除操作，都只需要一次旋转。
 - 如果我们的操作不是一个单一的操作，而是一个操作序列，那么使用分裂树的时间最少。

#### 2.3 字典的各种实现性能对比
| 方法 | 查找<br />（最坏情况） | 插入<br />（最坏情况） | 删除<br />（最坏情况） | 查找<br />（平均情况） | 插入<br />（平均情况） | 删除<br />（平均情况） |备注
|:---|:---:|:---:|:---:|:---:|:---:|:---:|---|
|有序数组|logn|n|n|logn|n|n|logn的查找性能是二分查找实现的|
|有序链表|n|n|n|n|n|n||
|哈希表|n|n|n|**1**|**1**|**1**||
|二叉搜索树|n|n|n|logn|logn|logn|当每一层只有一个节点时，就是最坏情况|
|AVL树|logn|logn|logn|logn|logn|logn||
|红黑树|**logn**|**logn**|**logn**|**logn**|**logn**|**logn**||
|分裂树|n|n|n|logn|logn|logn||
|B-树|logn|logn|logn|logn|logn|logn|适用于外部存储|
 - C\+\+ STL的[map](http://www.cplusplus.com/reference/map/map/?kw=map)/[multimap](http://www.cplusplus.com/reference/map/multimap/?kw=multimap)/[set](http://www.cplusplus.com/reference/set/set/?kw=set)/[multiset](http://www.cplusplus.com/reference/set/multiset/?kw=multiset)是基于红黑树实现的，[unordered_map](http://www.cplusplus.com/reference/unordered_map/unordered_map/?kw=unordered_map)/[unorder_multimap](http://www.cplusplus.com/reference/unordered_map/unordered_multimap/?kw=unordered_multimap)/[unordered_set](http://www.cplusplus.com/reference/unordered_set/unordered_set/?kw=unordered_set)/[unordered_multiset](http://www.cplusplus.com/reference/unordered_set/unordered_multiset/?kw=unordered_multiset) 是基于散列（哈希）实现的。
 - 在实际应用中，当我们要实施的操作都是按关键字进行查找、插入和删除时，应该选用哈希表来实现字典。<br/>但是当我们要求操作时间一定不能超过指定范围（最坏情况下需要最优），就应该使用红黑树来实现字典。<br/>对于按名次（有序）实施的查找和删除操作，或者可以不进行精确查找（如 查找关键字大于k的最小元素），也应该选用红黑树来实现字典。