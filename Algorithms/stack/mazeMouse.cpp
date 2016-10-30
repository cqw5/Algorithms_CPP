/*! Author: qwchen
 *! Date: 2016-9-20
 * 用栈实现的迷宫老鼠问题
 * 问题描述：给定一个迷宫，将一老鼠放在迷宫的入口，让老鼠寻找一条从迷宫入口到迷宫出口的路径
 * 思路：用一个栈来保存从入口到当前位置的路径，用一个长度为4的数组保存右下左上的顺时针操作移动顺序
 *       按照顺时针方向寻找下一个可以移动位置：
 *           若存在，则将当前位置入栈，当前指针指向下一个位置
 *           若不存在，则将出栈，将当前指针指向出栈的位置
 *       指导栈为空或者找到了迷宫出口为止
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 将一个点定义为一个结构体(x, y)
struct position{
    int row;
    int col;
    position(){}
    position(int row, int col) {
        this->row = row;
        this->col = col;
    }
};

/*
 * 从迷宫中maze寻找从入口start到出口end的路径path，返回路径是否存在和路径path
 * Parament:
 *     maze: 迷宫数组
 *     start：迷宫起点
 *     end：迷宫终点
 * Return：
 *     path：从起点到终点的路径
 *     bool：路径是否存在
 */
bool findPath(vector<vector<bool>> maze, position start, position end, stack<position> &path) {
    // 初始化偏移量
    position offset[4];
    offset[0].row = 0, offset[0].col = 1;  // 右
    offset[1].row = 1, offset[1].col = 0;  // 下
    offset[2].row = 0, offset[2].col = -1; // 左
    offset[3].row = -1, offset[3].col = 0; // 上
    // 当前位置
    position current = start;
    maze[1][1] = 1;     // 走过的位置标记1，防止重走
    int option = 0;
    int lastOption = 3;
    // 寻找路径
    // 循环终止条件：
    //     1. 找到迷宫终点
    //     2. 路径不存在，栈为空
    while (!((current.row == end.row) && (current.col == end.col))) {
        // 寻找当前结点的下一个可行结点
        while (option <= lastOption) {
            if (0 == maze[current.row + offset[option].row][current.col + offset[option].col])
                break;
            option++;
        }
        // 如果当前结点的下一个可行结点存在，将当前结点入栈，current指向其下一个结点(被current指针指过的结点都标记为1)
        if (option <= lastOption) {
            path.push(current);
            current.row += offset[option].row;
            current.col += offset[option].col;
            maze[current.row][current.col] = 1;
            option = 0;  // 复位
        } 
        // 如果当前结点的下一个可行结点不存在，出栈，当前指针指向刚刚出栈的元素
        else {
            if (path.empty()) { // 栈为空，路径不存在，退出
                return false;
            } else {
                position next = path.top();
                path.pop();
                if (next.row == current.row)
                    option = 3 + next.col - current.col;
                else
                    option = 2 + next.row - current.row;
                current = next;
            }
        }
    }
    return true;
}

/*
 * 输出路径
 */
void outpath(stack<position> &path) {
    vector<position> outPath;
    position top;
    while (!path.empty()) {
        outPath.push_back(path.top());
        path.pop();
    }
    for (int i = outPath.size() - 1; i >=0; i--){
        cout << "[" << outPath[i].row << ", " << outPath[i].col << "] ";
    }
    cout << endl;
    cout << "Mouse have escaped from the maze." << endl;
}


// 测试
void testMazeMouse() {
    const int numberOfRow = 10;
    const int numberOfCol = 10;
    // 10*10的迷宫矩阵，0和11是外围多了一圈障碍物，简化算法
    vector<vector<bool>> maze = {   
        { 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1 },
        { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
        { 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1 },
        { 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1 },
        { 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
    position start(1, 1); // maze[1][1]是迷宫的入口
    position end(10, 10); // maze[10][10]是迷宫的出口
    stack<position> path; // 用栈保存从迷宫入口到当前位置经过的路径
    if (findPath(maze, start, end, path)){
        cout << "Have Path" << endl;
        outpath(path);
    }
    else {
        cout << "No Path" << endl;
    }
}

int main(){
    testMazeMouse();
}