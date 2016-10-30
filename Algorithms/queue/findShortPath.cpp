/*! Author: qwchen
 *! Date: 2016-9-22
 * 用队列实现的查找迷宫中两点的最短路径
 * 问题描述：给定一个迷宫，和迷宫中任意两个点start和end，寻找从start到end的最短路径
 * 思路：一种广度优先搜索
 *       利用原始的迷宫矩阵(maze)来保存每个顶点到起点的距离。因为0被用来标记通路，1被标记障碍，因此我们从2开始计数，最后让距离都减去2即可。
 *       从起点开始，不断的将当前顶点的标记为0的邻居标记为当前顶点的标记+1，并将其入队列。然后从队头取出结点，重复该过程。
 *       直到找到end结点 或 队列为空（找不到end结点），结束循环。
 *       当能找到end结点时，maze每个非0和1结点就记录着该结点到start结点的距离+2，
 *       从end结点开始每次递减1方向搜索到start结点，并将该反向路径保存到栈中。
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// 将一个点定义为一个结构体(x, y)
struct position {
    int row;
    int col;
    position() {}
    position(int row, int col) {
        this->row = row;
        this->col = col;
    }
};

/*寻找迷宫两点最短路径的核心算法*/
bool findShortPath(vector<vector<int>> maze, position start, position end, stack<position> &path, int &pathLength) {
    if (start.row == end.row && start.col == end.col) {
        return true;
    }
    // 初始化偏移量
    position offset[4];
    offset[0].row = 0, offset[0].col = 1;  // 右
    offset[1].row = 1, offset[1].col = 0;  // 下
    offset[2].row = 0, offset[2].col = -1; // 左
    offset[3].row = -1, offset[3].col = 0; // 上
    int numberOfNeig = 4;
    position current = start;
    maze[current.row][current.col] = 2;  // 用0代表未走的结点，1代表障碍，>=2的数代表距离，最后将距离都-2就可以得到真正的距离
    position neig;
    queue<position> queue;
    while (true) {
        // 对一个结点的周围是个结点，如果不是end结点、不是障碍结点、也不是走过的结点，
        // 则标记为当前结点的距离+1，并放到队列中
        for (int i = 0; i < numberOfNeig; i++) {
            neig.row = current.row + offset[i].row;
            neig.col = current.col + offset[i].col;
            if (maze[neig.row][neig.col] == 0) {
                maze[neig.row][neig.col] = maze[current.row][current.col] + 1;
                queue.push(neig);
            }
            // 如果找到end结点，退出死循环
            if (neig.row == end.row && neig.col == end.col) {
                break;
            }
        }
        if (neig.row == end.row && neig.col == end.col) { // 找到时结束死循环
            break;    
        }
        // 队列为空时，说明找不到end结点，结束死循环，返回false
        if (queue.empty()) { 
            return false;
        }
        current = queue.front();
        queue.pop();
    }
    pathLength = maze[end.row][end.col] - 2;
    current = end;
    for (int i = pathLength - 1; i >= 0; i--) {
        path.push(current);
        for (int j = 0; j < numberOfNeig; j++) {
            neig.row = current.row + offset[j].row;
            neig.col = current.col + offset[j].col;
            if (maze[neig.row][neig.col] == i + 2) 
                break;
        }
        current = neig;
    }
    path.push(start);
    return true;
}


void testfindShortPath() {
    const int numberOfRow = 7;
    const int numberOfCol = 7;
    // 7 * 7的迷宫矩阵，0和8是外围多了一圈障碍物，简化算法
    // 矩阵0表示可走路径，1表示障碍物
    vector<vector<int>> maze = {
        { 1,1,1,1,1,1,1,1,1 },
        { 1,0,0,1,0,0,0,0,1 },
        { 1,0,0,1,1,0,0,0,1 },
        { 1,0,0,0,0,1,0,0,1 },
        { 1,0,0,0,1,1,0,0,1 },
        { 1,1,0,0,0,1,0,0,1 },
        { 1,1,1,1,0,0,0,0,1 },
        { 1,1,1,1,0,0,0,0,1 },
        { 1,1,1,1,1,1,1,1,1 }
    };
    for (int i = 0; i < numberOfRow + 2; i++) {
        for (int j = 0; j < numberOfCol + 2; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    int pathLength = 0;    // 最短路径长度
    stack<position> path;  // 最短路径队列
    position start(3, 2);  // 起点
    position end(4, 6);    // 终点
    if (findShortPath(maze, start, end, path, pathLength)) {
        cout << "Have short path. ";
        cout << "It 's long is " << pathLength << "." << endl;
        while(!path.empty()){
            position current = path.top();
            path.pop();
            cout << "(" << current.row << ", " << current.col << ")" << endl;
        }
    }
    else {
        cout << "No short path." << endl;
    }
}

int main(){
    testfindShortPath();
}