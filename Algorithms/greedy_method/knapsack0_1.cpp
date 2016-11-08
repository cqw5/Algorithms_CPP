/*! Author: qwchen
 *! Date  : 2016-10-17
 * 
 * 0/1背包问题的贪心解法
 * 问题描述：
 * * 有n个物品和一个容量为c的背包，从n个物品中选取装包的物品。物品i的重量为w_i，价值为p_i。
 * * 一个可行的装载指：装包的物品总重量不超过背包的容量。
 * * 一个最佳的背包指：物品总价值最高的可行背包装载。
 * 求最佳的背包？
 * 0/1背包问题是一个NPC问题
 * 思路：采用k阶优化 + 价值密度p_i/w_i贪婪法则。 
 *       首先将最多k件物品放入背包中，如果这k件物品重量大于c，则放弃它。否则，根据背包剩余的容量，考虑将剩余物品按p_i/w_i的非递增顺序装入背包。
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 物品类
class Item {
public:
    Item(){}
    Item(int id, int price, int weight){
        id_ = id;
        price_ = price;
        weight_ = weight;
        unit_weight_price_ = 1.0 * price_ / weight_; 
    }
    int getId(){
    	return id_;
    }
    int getPrice(){
    	return price_;
    }
    int getWeight(){
    	return weight_;
    }
    operator double() const{
    	return unit_weight_price_;
    }
private:
    int id_;                    // 商品id
    int price_;                 // 商品价值
    int weight_;                // 商品质量
    double unit_weight_price_;  // 商品的单位质量的价值
};

/*
 * Parament:
 *     arr是原始存储所有元素的数组
 *     data是保存当前组合结果的数组
 *     result是保存所有组合结果的数组
 *     start, end是原始数组中未被选择的剩余数组中元素的起始位置和终止位置
 *     index是已经找到的组合数的个数
 *     r是总共需要的组合数的个数
 */
template <class T>
void combination(T arr, T &data, vector<T> &result, int start, int end, int index, int r){
    if (index == r){
        result.push_back(data);
    } 
    else if (end - start < r - index){
        return;
    }
    else{
        data[index] = arr[start];
        combination(arr, data, result, start + 1, end, index + 1, r);
        combination(arr, data, result, start + 1, end, index, r);
    }
}

/*
 * Parament:
 *     item_id_arr: 商品的id数组
 *     item_arr: 商品的数组
 *     c: 背包的最大容量
 *     k: k阶
 * Return：
 *     vector<int>: 放到背包中的商品id数组
 */
vector<int> knapsack(vector<int> item_id_arr, vector<Item> item_arr, int c, int k){
    // 保存背包最大价值 及其 对应的商品id列表 
    int total_max_price = 0;                 // 最大的价值
    vector<int> total_max_price_item_id_arr; // 最大价值的背包对应商品的id列表
    for (int r = 1; r <= k; r++){            // k选取k阶优化中最大价值的背包
        // 选取k阶组合result
        vector<int> data(r);
        vector<vector<int>> result;          // 记录所有可能的k阶组合
        combination(item_id_arr, data, result, 0, item_id_arr.size(), 0, r);
        // 对每一种k阶组合，首先将最多k件物品放入背包中：
        //   如果这k件物品重量大于c，则放弃它。
        //   否则，根据背包剩余的容量，考虑将剩余物品按p_i/w_i的非递增顺序装入背包。
        for (auto items: result){
            // 求商品列表与选取的k个商品的差集
            sort(items.begin(), items.end());
            vector<int> item_id_list_remainer(item_id_arr.size() - items.size());  // 去除k阶商品后的商品id列表
            set_difference(item_id_arr.begin(), item_id_arr.end(), items.begin(), items.end(), item_id_list_remainer.begin()); // 差集
            vector<int> current_max_price_item_id;          // 当前背包中的商品id列表
            int current_max_price = 0;                      // 当前背包中商品的总价值
            int current_max_weight = 0;                     // 当前背包中商品的总重量
            for (auto item: items){
                current_max_price_item_id.push_back(item);
                current_max_price += item_arr[item].getPrice();
                current_max_weight += item_arr[item].getWeight();
            }
            if (current_max_weight > c){                    // 加入k阶时，背包已经超重，则删除该组组合
                continue;
            }
            vector<Item> item_arr_remainer;                 // 选取k阶后，剩余的商品
            for (auto id: item_id_list_remainer){           
                item_arr_remainer.push_back(item_arr[id]);
            }
            // 将商品按价值密度从大到小排序，不断选取剩余商品列表中价值密度最大的商品加入到背包
            sort(item_arr_remainer.begin(), item_arr_remainer.end(), greater<double>());
            for (int i = 0; i < item_arr_remainer.size(); i++){
                if(current_max_weight + item_arr_remainer[i].getWeight() > c) {
                    continue;
                }
                current_max_weight += item_arr_remainer[i].getWeight();
                current_max_price += item_arr_remainer[i].getPrice();
                current_max_price_item_id.push_back(item_arr_remainer[i].getId());
            }
            // 如果当前的背包最大价值 对于 前面求出的背包的最大价值，替换
            if (current_max_price > total_max_price){
                total_max_price_item_id_arr.clear();
                for (auto id: current_max_price_item_id){
                    total_max_price_item_id_arr.push_back(id);
                }
            }
        }
    }
    return total_max_price_item_id_arr;
}

// 测试组合函数
void testCombination(){
    vector<int> arr = {1,2,3,4};
    int r = 2;
    vector<int> data(r);
    vector<vector<int>> result;
    combination(arr, data, result, 0, arr.size(), 0, r);
    for (auto elems: result){
        cout << "( ";
        for (auto elem: elems){
            cout << elem << " ";
        }
        cout << ")" << endl;
    }
}

void testKnapsack(){
    int c = 11;
    Item item0(0, 6, 2);
    Item item1(1, 10, 4);
    Item item2(2, 12, 6);
    Item item3(3, 13, 7);
    vector<Item> item_arr = {item0, item1, item2, item3};
    vector<int> item_id_arr = {0, 1, 2, 3};
    int k = 2;
    vector<int> max_price_item_id_arr = knapsack(item_id_arr, item_arr, c, k);
    int max_price = 0;
    cout << "Max price list: ";
    for (auto id: max_price_item_id_arr){
        cout << id << " ";
        max_price += item_arr[id].getPrice();
    }
    cout << endl;
    cout << "It's price is " << max_price << endl;
}

int main(){
    //testCombination();
    testKnapsack();
    return 0;
}


