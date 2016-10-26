/*!
 * 矩阵乘法链：确定一个最优的矩阵乘法顺序    的    动态规划递归解法和迭代解法
 * 问题描述：已知矩阵乘法满足结合律，现给定一个q个矩阵连乘的序列，用r[i]表示第i个矩阵的行数，r[i+1]表示第i个矩阵的列数，求最优的乘法顺序。
 * 直接搜索所有可能的乘法序列，时间复杂度为O(2^q)，是一个NPC问题的最优化问题
 * 思路：1.递归方程：(下标从1开始)
 *         用M_ij表示乘积链 M_i * ... * M_j
 *         用c(i,j)表示用最优法计算M_ij时的时耗
 *         用kay(i,j)表示最优的c(i,j)中最后一步乘法M_ik * M_kj时的k，即最优c(i,j)的最后一步乘法的乘号在第kay(i,j)个位置上
 *         | c(i,i) = 0,                                                      1 <= i <= q
 *         | c(i,i+1) = r_i * r_(i+1) * r_(i+2),                              1 <= i < q
 *         |     kay(i,i+1) = i,                                              1 <= i < q
 *         | c(i,i+s) = min{c(i,k) + c(k+1,i+s) + r_i * r_(k+1) * r_(i+s+1)}, 1 <= i <= q-s, 1 <= s < q, i <= k < i+s
 *         |     kay(i,i+s) = 最优的c(i,i+s)中的k
 *       2.用一个二维数组c[i][j]存储所有的c(i,j)，c的元素初始值都为0，
 *         若遇到c(i,j)不为0，说明前面已经计算过该c(i,j)，则不用在重新计算，从而避免重复子问题的计算
 *         用一个二维数组kay[i][j]存储所有的kay(i,j)
 *       3.自上而下递归kay就可以求得最佳的乘法顺序
 * 时间复杂度O(q^3)
 */

#include <iostream>
#include <vector>

using namespace std;

class MatrixChain{
public:
    /*
     * 动态规划的递归解法
     * Parament：
     *     q: 矩阵个数
     *     r: 矩阵的维数组
     */ 
    static void matrixChainRecurence(int q, vector<int> &r){
        vector<vector<int>> theC(q, vector<int>(q, 0));  // theC[i][j]表示用最优法计算M_ij(M_i * ... * M_j)时的时耗
        vector<vector<int>> kay(q, vector<int>(q, 0));   // kay(i,j)表示最优的c(i,j)中最后一步乘法M_ik * M_kj时的k
        int minC = c(q, r, theC, kay, 0, q - 1);         // 迭代求解所有矩阵相乘的时好
        cout << "min cost is " << minC << endl;          
        trackback(kay, 0, q - 1);                        // 递归输出
    }

    /*
     * 动态规划的迭代解法
     * Parament：
     *     q: 矩阵个数
     *     r: 矩阵的维数组
     */ 
    static void matrixChainIterator(int q, vector<int> &r){
        vector<vector<int>> theC(q, vector<int>(q, 0));
        vector<vector<int>> kay(q, vector<int>(q, 0));
        // 由于theC初始值都为0，省略theC[i][i] = 0的计算
        // 计算theC[i][i+1]
        // c(i,i+1) = r_i * r_(i+1) * r_(i+2), 1 <= i < q
        // kay(i,i+1) = i, 1 <= i < q
        for (int i = 0; i < q - 1; i++) {
            theC[i][i+1] = r[i] * r[i+1] * r[i+2];
            kay[i][i+1] = i;
        }
        // 计算s = 2 ... q - 1
        // c(i,i+s) = min{c(i,k) + c(k+1,i+s) + r_i * r_(k+1) * r_(i+s+1)}, 1 <= i <= q-s, 1 <= s < q, i <= k < i+s
        // kay(i,i+s) = 最优的c(i,i+s)中的k
        for (int s = 2; s < q; s++) {
            for (int i = 0; i < q - s; i++){
                theC[i][i+s] = theC[i][i] + theC[i+1][i+s] + r[i] * r[i+1] * r[i+s+1];
                kay[i][i+s] = i;
                for (int k = i + 1; k < i + s; k++){
                    int newC = theC[i][k] + theC[k+1][i+s] + r[i] * r[k+1] * r[i+s+1];
                    if (newC < theC[i][i+s]){
                        theC[i][i+s] = newC;
                        kay[i][i+s] = k;
                    } 
                }
            }
        }
        cout << "min cost is " << theC[0][q-1] << endl;
        trackback(kay, 0, q - 1);
    }

private:
    /*
     * 计算theC[i][j]
     * Parament:
     *     q: 矩阵个数
     *     r: 矩阵的维数组
     *     theC: theC[i][j]表示用最优法计算M_ij(M_i * ... * M_j)时的时耗
     *     kay: kay(i,j)表示最优的c(i,j)中最后一步乘法M_ik * M_kj时的k
     *     i, j: 数组下标
     * Return:
     *     theC[i][j]的值
     */
    static int c(int q, vector<int> &r, vector<vector<int>> &theC, vector<vector<int>> &kay, int i, int j){
        // theC[i][j]初始值为0，如果当前theC[i][j]不为0，说明theC[i][j]已经计算过，是重叠子问题
        if (theC[i][j] > 0) return theC[i][j];
        // 还没计算过的情况
        // c(i,i) = 0, 1 <= i <= q
        if (i == j){
            return 0;
        }
        // c(i,i+1) = r_i * r_(i+1) * r_(i+2), 1 <= i < q
        // kay(i,i+1) = i, 1 <= i < q
        if (j == i + 1){
            theC[i][j] = r[i] * r[i+1] * r[i+2];
            kay[i][j] = i;
            return theC[i][j];
        }
        // c(i,i+s) = min{c(i,k) + c(k+1,i+s) + r_i * r_(k+1) * r_(i+s+1)}, 1 <= i <= q-s, 1 <= s < q, i <= k < i+s
        // kay(i,i+s) = 最优的c(i,i+s)中的k
        kay[i][j] = i;
        theC[i][j] = c(q, r, theC, kay, i, i) + c(q, r, theC, kay, i+1, j) + r[i] * r[i+1] * r[j+1];
        for (int k = i + 1; k < j; k++){
            int newC = c(q, r, theC, kay, i, k) + c(q, r, theC, kay, k+1, j) + r[i] * r[k+1] * r[j+1];
            if (newC < theC[i][j]){
                theC[i][j] = newC;
                kay[i][j] = k;
            }
        }
        return theC[i][j];
    }

    /*
     * 输出M_ij的最佳计算顺序
     */
    static void trackback(vector<vector<int>> &kay, int i, int j){
        if (i == j) return;
        trackback(kay, i, kay[i][j]);
        trackback(kay, kay[i][j] + 1, j);
        cout << "M_" << i << "," << kay[i][j] << " * M_" << (kay[i][j] + 1) << "," << j << endl;
    }
    
};


void testMatrixChain(){
    int q = 5; // 矩阵的个数
    vector<int> r = {10, 5, 1, 10, 2, 10};    // 5个矩阵分别为：q[0]:10 * 5, q[1]:5 * 1, q[2]:1 * 10, q[3]:10 * 2, q[4]:2 * 10
    MatrixChain::matrixChainRecurence(q, r);  // 测试动态规划递归解法
    MatrixChain::matrixChainIterator(q, r);   // 测试动态规划迭代解法
}

int main(){
    testMatrixChain();
    return 0;
}


