/*！
 * 0/1背包问题的动态规划递归解法 和 迭代解法
 * 问题描述：
 * * 有n个物品和一个容量为c的背包，从n个物品中选取装包的物品。物品i的重量为w_i，价值为p_i。
 * * 一个可行的装载指：装包的物品总重量不超过背包的容量。
 * * 一个最佳的背包指：物品总价值最高的可行背包装载。
 * 求最佳的背包？
 * 0/1背包问题是一个NPC问题
 * 思路：1.递归方程：(下标从1开始)
 *        最后一个数：
 *        f(n, k) = | p_n,  k >= w_n 
 *                  | 0,    0 < k < w_n
 *        前n-1个数
 *        f(i, k) = | max{f(i+1, k), f(i+1, k-w_i)+p_i},  k >= w_i
 *                  | f(i+1, k),                          0 < k < w_i
 *       2.用一个整型数组fArray[物品个数n][背包的容量c]来保存所有的状态，fArray[i][k]表示对于第i个物品，当前背包剩余容量为k时，装载的价值。
 *         则fArray[1]中最大的fArray[1][k]就是最大装载价值。
 *       3.利用fArray[i][k] == fArray[i+1][k]，若为true，说明i没有被装载；若为false，说明i被装载。
 * 时间复杂度：O(cn)
 */

#include <iostream>
#include <vector>

using namespace std;

// 物品的结构体
struct Item {
    int id;       // 物品的id
    int weight;   // 物品的重量
    int price;    // 物品的价值
    Item(int theId, int theWeight, int thePrice){
        id = theId; weight = theWeight; price = thePrice;
    }
};

class Knapsack{
public:
    /*
     * 递归解法
     * 调用f函数递归求解状态数组，然后用trackback回溯求最佳装载物品
     * Parament:
     *     item: 物品项
     *     numberOfItem: 物品项的个数
     *     numberOfCapacity: 背包的容量
     *     x: 最佳背包
     * Return：
     *     x: 最佳背包
     *     maxPrice: 最优背包的价值(最大价值)
     */
    static int knapsack_recurence(vector<Item> &item, int numberOfItem, int numberOfCapacity, vector<int> &x){
        vector<vector<int>> fArray(numberOfItem + 1, vector<int>(numberOfCapacity + 1, 0));  // 保存状态的数组
        int maxPrice = f(item, 1, numberOfItem, numberOfCapacity, fArray);                   // 递归求解状态数组
        trackback(item, numberOfItem, numberOfCapacity, fArray, x);                          // 回溯求解装载物品
        return maxPrice;
    }
    
    /*
     * 迭代解法
     * Parament:
     *     item: 物品项
     *     numberOfItem: 物品项的个数
     *     numberOfCapacity: 背包的容量
     *     x: 最佳背包
     * Return：
     *     x: 最佳背包
     *     maxPrice: 最优背包的价值(最大价值)
     */
    static int knapsack_iterator(vector<Item> item, int numberOfItem, int numberOfCapacity, vector<int> &x){
        vector<vector<int>> fArray(numberOfItem + 1, vector<int>(numberOfCapacity + 1, 0));  // 保存状态数组
        // 初始化最后一个物品的状态fArray[numberOfItem]，根据递归公式
        int yMax = min(item[numberOfItem].weight - 1, numberOfCapacity);
        // // f(n, k) = 0,  k < w_n 
        for (int i = 1; i < yMax; i++){
            fArray[numberOfItem][i] = 0;
        }
        // f(n, k) = p_n,  k >= w_n 
        for (int i = item[numberOfItem].weight; i <= numberOfCapacity; i++){
            fArray[numberOfItem][i] = item[numberOfItem].price;
        }
        // 初始化2到numberOfItem-1个物品的状态，根据递推公式
        for (int i = numberOfItem - 1; i > 1; i--){
            // f(i, k) = f(i+1, k),  0 < k < w_i
            yMax = min(item[i].weight - 1, numberOfCapacity);
            for (int j = 1; j < yMax; j++){
                fArray[i][j] = fArray[i+1][j];
            }
            // f(i, k) = max{f(i+1, k), f(i+1, k-w_i)+p_i},  k >= w_i
            for (int j = item[i].weight; j <= numberOfCapacity; j++){
                fArray[i][j] = max(fArray[i+1][j], fArray[i+1][j - item[i].weight] + item[i].price);
            }
        }
        // 对于第一个元素，numberOfCapacity一定是满的，因此只需初始化item[1][numberOfCapacity]
        if(numberOfCapacity >= item[1].weight){
            fArray[1][numberOfCapacity] = max(fArray[2][numberOfCapacity], fArray[2][numberOfCapacity - item[1].weight] + item[1].price);
        } else {
            fArray[1][numberOfCapacity] = fArray[2][numberOfCapacity];
        }
        trackback(item, numberOfItem, numberOfCapacity, fArray, x);                          // 回溯求解装载物品
        int maxPrice = 0;
        for (int i = 1; i <= numberOfItem; i++){
            if (x[i] != 0){
                maxPrice += item[i].price;
            }
        }
        return maxPrice;
    }

private:
    /*
     * 递归求解状态数组
     * Parament:
     *     item: 物品项
     *     i: 当前物品
     *     n: 物品项的总数
     *     k: 当前背包剩余容量
     *     fArray: 状态数组
     * Return:
     *     fArray: 状态数组
     *     fArray[i][k]: 
     */
    static int f(vector<Item> &item, int i, int n, int k, vector<vector<int>> &fArray){
        // fArray[i][k]初始值为0，如果当前fArray[i][k]不为0，说明fArray[i][k]已经计算过，是重叠子问题
        if (fArray[i][k] > 0) {
            return fArray[i][k];
        }
        // 还没计算过的情况
        // i是最后一个物品 
        if (i == n){
            if (k >= item[i].weight) fArray[i][k] = item[i].price;  // 背包所剩容量还能装下该物品，就装下
            else                     fArray[i][k] = 0;              // 背包所剩容量不能装下该物品了
            return fArray[i][k];
        }
        // i不是最后一个物品
        if (k < item[i].weight){  // 背包所剩容量不能装下该物品了
            fArray[i][k]  = f(item, i+1, n, k, fArray);
        } 
        else {                    // 背包所剩容量还能装下该物品，尝试两种可能（装与不装），取最优
            fArray[i][k]  = max(f(item, i+1, n, k, fArray),  f(item, i+1, n, k - item[i].weight, fArray) + item[i].price);
        }
        return fArray[i][k];
    }

    /*
     * Parament:
     *     item: 物品项
     *     numberOfItem: 物品项的个数
     *     numberOfCapacity: 背包的容量
     *     fArray: 状态数组
     *     x: 最佳背包
     * Return:
     *     x: 最佳背包
     */ 
    static void trackback(vector<Item> &item, int numberOfItem, int numberOfCapacity, vector<vector<int>> &fArray, vector<int> &x){
        for (int i = 1; i < numberOfItem; i++){
            if (fArray[i][numberOfCapacity] == fArray[i+1][numberOfCapacity]){
                x[i] = 0;
            }
            else {
                x[i] = 1;
                numberOfCapacity -= item[i].weight;
            }
        }
        if (numberOfCapacity >= item[numberOfItem].weight){
            x[numberOfItem] = 1;
        } else {
            x[numberOfItem] = 0;
        }
    }
};


void testKnapsack(){
    int numberOfItem = 5;
    int numberOfCapacity = 10;
    Item item0(0, 0, 0);
    Item item1(1, 2, 6);
    Item item2(2, 2, 3);
    Item item3(3, 6, 5);
    Item item4(4, 5, 4);
    Item item5(5, 4, 6);
    vector<Item> item = {item0, item1, item2, item3, item4, item5};
    vector<int> x(numberOfItem + 1, 0);
    // int maxPrice = Knapsack::knapsack_recurence(item, numberOfItem, numberOfCapacity, x);  // 测试递归版本
    int maxPrice = Knapsack::knapsack_iterator(item, numberOfItem, numberOfCapacity, x);   // 测试迭代版本 
    cout << "Max price list: ";
    for (int i = 1; i <= numberOfItem; i++){
        if (x[i] != 0){
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "It's price is " << maxPrice << endl;
}

int main(){
    testKnapsack();
    return 0;
}





