/*! Author: qwchen
 *! Date: 2016-9-19
 * 递归实现汉诺塔问题
 * 时间复杂度：O(2^n)
 */

#include <iostream>

using namespace std;

void towersOfHanoi(int n, int x, int y, int z){
    if (n > 0) {
        towersOfHanoi(n-1, x, z, y);  // 先将x的前n-1个碟子移动到z，用y作为中转
        cout << "Move top disk from tower " << x << " to top of tower " << y << endl;  // 将第n个碟子从x移动到y
        towersOfHanoi(n-1, z, y, x);  // 再将前n-1个碟子从z移动到y，用x作为中转
    }
}

int main(){
    towersOfHanoi(4, 1, 2, 3);
    return 0;
}
