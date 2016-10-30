/*! Author: qwchen
 *! Date: 2016-9-21
 * 用栈实现的列车重排序问题
 * 问题描述：给定一两车厢乱序的列车"尾[581742963]头"于入轨道中和k个缓冲轨道(缓存轨道只能后进先出)，
 *           利用这些缓冲轨道对车厢进行重排列，使得列车到达出轨道时车厢顺序为"尾[987654321]头"
 *           限制：1. 车厢可以从入轨道的前端移动到一个缓冲轨道的顶部或出轨道的后端
 *                 2. 车厢可以从一个缓冲轨道的顶部移到出轨道的后端
 * 思路：将每一个缓冲轨道定义为一个栈，保存一个缓冲轨道最小车厢的标记smallestCar及其所在轨道的编号itsTrack，记录下一个要入到出轨道的车厢号nextCarToOutput
 *       对于入轨道的每一节车厢：
 *           如果它刚好等于下一个要入到出轨道的车厢号，直接将其从入轨道移动到出轨道。
 *               此时，不断检查缓冲轨道中最小的车厢号是否等于下一个要入到出轨道的车厢号，若是则将其入到出轨道
 *           否则，将其移动到缓冲轨道。
 *               缓冲轨道的选取原则是：编号为u的车厢要入的轨道应该是车厢编号大于u的最小者
 */


#include <iostream>
#include <stack>

using namespace std;

// 全局变量
stack<int> *track;      // 缓冲轨道数组
int numberOfCars;       // 车厢的数目
int numberOfTracks;     // 缓冲轨道的数目
int smallestCar;        // 在缓冲轨道中编号最小的车厢
int itsTrack;           // 停靠着最小车厢的缓存轨道


void outputFromHoldingTrack();
bool putInHoldingTrack(int c);

/*
 * 列车车厢重排列
 * Parament：
 *     inputOrder: 入轨道的车厢
 *     theNumberOfCars: 车厢数量
 *     theNumberOfTracks: 缓冲轨道的数量
 */
bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks) {
    numberOfCars = theNumberOfCars;
    numberOfTracks = theNumberOfTracks;
    track = new stack<int>[numberOfTracks];
    int nextCarToOutput = 1;  // 记录下一个要入到出轨道的车厢号
    smallestCar = numberOfCars;
    for (int i = 0; i < numberOfCars; i++) {         // 遍历入轨道的每一个车厢
        if (inputOrder[i] == nextCarToOutput) {      // 如果刚好等于下一个要入到出轨道的车厢号，直接出道出轨道
            cout << "Move car " << inputOrder[i] << " from input track to output stack" << endl;
            nextCarToOutput++;
            while (smallestCar == nextCarToOutput) { // 缓冲区也可能有可以到出轨道的车厢
                outputFromHoldingTrack();
                nextCarToOutput++;
            }
        }
        else {    // 如果不等于下一个要入到出轨道的车厢号，入到缓冲轨道
            if (!putInHoldingTrack(inputOrder[i]))
                return false;
        }
    }
    return true;
}

/*
 * 将编号最小的车厢从缓冲轨道移到出轨道
 */
void outputFromHoldingTrack() {
    // 将当前缓冲区中最小的元素移到出轨道
    cout << "Move car " << smallestCar << " from buffer track " << itsTrack << " to output stack" << endl;
    if(!track[itsTrack].empty())
        track[itsTrack].pop();
    // 遍历所有栈顶，重选选举最小元素
    smallestCar = numberOfCars;
    for (int i = 0; i < numberOfTracks; i++) {
        if (!track[i].empty() && track[i].top() < smallestCar) {
            smallestCar = track[i].top();
            itsTrack = i;
        }
    }
}

/* 
 * 将车厢c移动到一个缓冲轨道。 若没有可用缓冲轨道，返回false
 * Parament：
 *     c：车厢号
 */
bool putInHoldingTrack(int c) {
    // 寻找车厢c要移入的缓冲轨道
    int bestTrack = numberOfTracks;        // 预选的轨道
    int bestTop = numberOfCars;            // 预选轨道当前的top车厢
    for (int i = 0; i < numberOfTracks; i++) {
        if (track[i].empty()) {
            if (bestTrack == numberOfTracks) bestTrack = i;  // 除非找不到可用的栈，才使用空栈
        }
        else {
            int topCar = track[i].top();
            if (c < topCar && topCar < bestTop) {
                bestTrack = i;
                bestTop = topCar;
            }
        }
    }
    if (bestTrack == numberOfTracks)
        return false;
    track[bestTrack].push(c);
    cout << "Move car " << c << " to buffer track " << bestTrack << endl;
    // 更新在缓冲轨道中编号最小的车厢
    if (c < smallestCar) {
        smallestCar = c;
        itsTrack = bestTrack;
    }
    return true;
}

void testRailroad() {
    int inputOrder[9] = { 5, 8, 1, 7, 4, 2, 9, 6, 3 };
    if (railroad(inputOrder, 9, 3))
        cout << "alreadly correct sorted" << endl;
    else
        cout << "unable to sorted, buffer stack lack" << endl;
}

int main(){
    testRailroad();
}