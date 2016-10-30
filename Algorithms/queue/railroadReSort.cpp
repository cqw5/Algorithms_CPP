/*! Author: qwchen
 *! Date: 2016-9-22
 * 用队列实现的列车重排序问题
 * 问题描述：给定一两车厢乱序的列车"尾[581742963]头"于入轨道中和k个缓冲轨道(缓存轨道只能先进先出)，
 *           利用这些缓冲轨道对车厢进行重排列，使得列车到达出轨道时车厢顺序为"尾[987654321]头"
 *           限制：1. 车厢可以从入轨道的前端移动到一个缓冲轨道的后端或出轨道的后端
 *                 2. 车厢可以从一个缓冲轨道的前端移到出轨道的后端
 * 思路：将每一个缓冲轨道定义为一个队列，保存一个缓冲轨道最小车厢的标记smallestCar及其所在轨道的编号itsTrack，记录下一个要入到出轨道的车厢号nextCarToOutput
 *       对于入轨道的每一节车厢：
 *           如果它刚好等于下一个要入到出轨道的车厢号，直接将其从入轨道移动到出轨道。
 *               此时，不断检查缓冲轨道中最小的车厢号是否等于下一个要入到出轨道的车厢号，若是则将其入到出轨道
 *           否则，将其移动到缓冲轨道。
 *               缓冲轨道的选取原则是：编号为u的车厢要入的轨道应该是车厢编号小于u的最大者
 */

#include <iostream>
#include <queue>

using namespace std;

// 全局变量
queue<int> *track;    // 缓冲轨道数组
int numberOfCars;     // 车辆的数目
int numberOfTracks;   // 缓冲轨道的数目
int smallestCar;      // 在缓冲轨道中编号最小的车厢
int itsTrack;         // 停靠着最小车厢的缓存轨道

void outputFromHoldingTrack();
bool putInHoldingTrack(int inputCar);

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
    track = new queue<int>[numberOfTracks];
    int nextCar = 1;  // 记录下一个要入到出轨道的车厢号
    smallestCar = numberOfCars + 1;
    itsTrack = numberOfTracks + 1;
    for (int i = 0; i < numberOfCars; i++) {
        if (inputOrder[i] == nextCar) { // 1. 直接从入轨道移到出轨道
            cout << "Move car " << inputOrder[i] << " from input track to output stack" << endl;
            nextCar++;
            while (smallestCar == nextCar) { // 2. 从缓冲轨道移到出轨道
                outputFromHoldingTrack();
                nextCar++;
            }
        }
        else {    // 3. 从入轨道移动缓冲轨道
            if (!putInHoldingTrack(inputOrder[i])) {
                return false;
            }
        }
    }
    return true;
}

// 2. 从缓冲轨道移到出轨道
void outputFromHoldingTrack() {
    // 从缓冲轨道移到出轨道
    cout << "Move car " << smallestCar << " from holding track " << itsTrack << " to output stack" << endl;
    track[itsTrack].pop();
    // 重新选举队尾最小的车及其队号
    smallestCar = numberOfCars + 2;
    itsTrack = numberOfTracks + 1;
    for (int i = 0; i < numberOfTracks; i++) {
        if (!track[i].empty() && track[i].front() < smallestCar) {
            smallestCar = track[i].front();
            itsTrack = i;
        }
    }
}

// 3. 从入轨道移动缓冲轨道
bool putInHoldingTrack(int inputCar) {
    int bestTrack = numberOfTracks;
    int bestTop = 0;
    for (int i = 0; i < numberOfTracks; i++) {
        if (!track[i].empty()) {
            int lastCar = track[i].back();
            if (lastCar > bestTop && lastCar < inputCar) {
                bestTop = lastCar;
                bestTrack = i;
            }
        }
        else {
            if (bestTop == 0)
                bestTrack = i;
        }
    }
    if (bestTrack == numberOfTracks)
        return false;
    track[bestTrack].push(inputCar);
    cout << "Move Car " << inputCar << " from input track to holding track " << bestTrack << endl;
    if (inputCar < smallestCar) {
        smallestCar = inputCar;
        itsTrack = bestTrack;
    }
    return true;
}


void testRailroad() {
    int inputOrder[9] = {3, 6, 9, 2, 4, 7, 1, 8, 5};
    if(railroad(inputOrder, 9, 2))
        cout << "[Successd] All cars have moved from input track to output stack" << endl;
    else
        cout << "[Failed] No enough track!!!" << endl;
}


int main(){
    testRailroad();
    return 0;
}