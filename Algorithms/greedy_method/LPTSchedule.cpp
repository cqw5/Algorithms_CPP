/*! Author: qwchen
 *! Date  : 2016-10-17
 * 
 * 机器调度问题：
 * 一个工厂有m台一模一样的机器，有n个任务要处理。
 * * 一台机器在同一个时间内只能处理一个作业
 * * 一个作业不能同时在两台机器上处理
 * * 执行每个任务所需要的时间不同（即每个任务都有一个属性：时间）
 * 求最少的调度时间？
 * 这是一个NPC问题，采用近似算法来解决。
 * 思路：采用LPT算法，将作业按处理时间递减顺序排序。当一个作业需要分配时，总是分配给最先变为空闲的机器。
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 任务结点(任务的ID + 执行任务所需要的时间)
class jobNode {
public:
    jobNode(){}
    jobNode(int id, int time){
    	id_ = id;
    	time_ = time;
    }
    int getId(){
    	return id_;
    }
    int getTime(){
    	return time_;
    }
    operator int() const { // 定义通过time来比较jobNode的大小
    	return time_;
    }
private:
    int id_,    // 执行任务的ID
        time_;  // 执行任务所需要的时间
};

// 机器结点(机器ID + 当前机器开始空闲的时间)
class machineNode {
public:
	machineNode(){}
    machineNode(int id, int avail){
        id_ = id;
        avail_ = avail;
    }
    int getId(){
    	return id_;
    }
    int getAvail(){
    	return avail_;
    }
    void setAvail(int avail){
        avail_ = avail;	
    }
    operator int() const {
    	return avail_;
    }
private:
    int id_,      // 机器ID
        avail_;   // 当前机器开始的空闲时间
};

/*
 * 机器调度的贪心算法
 * Parament:
 *     job: vector<jobNode>, 任务结点集合
 *     machine: vector<machine>, 机器结点集合
 *     num_job: int, 任务结点数
 *     num_machine: 机器结点数
 */
void makeSchedule(vector<jobNode> job, vector<machineNode> machine, int num_job, int num_machine){
    // 如果机器数大于等于任务数，直接分配即可
    if (num_machine >= num_job){
    	cout << "Schedule each job on a different machine." << endl;
    	return;
    }
    // 先对任务从大到小排序
    sort(job.begin(), job.end(), greater<int>());
    // 对机器列表构建小顶堆
    make_heap(machine.begin(), machine.end(), greater<int>());
    for (int i = 0; i < num_job; i++){
    	// 每次总是从堆中去avail最小的机器来分配任务
        machineNode avail_machine = machine.front();
        pop_heap(machine.begin(), machine.end(), greater<int>()); machine.pop_back();
        cout << "Schedule job " << job[i].getId() << " on machine " << avail_machine.getId()
            << " from " << avail_machine.getAvail() 
            << " to " << (avail_machine.getAvail() + job[i].getTime()) 
            << endl;
        // 将机器的avail加上新的任务的运行时间，重新放入堆中
        avail_machine.setAvail(avail_machine.getAvail() + job[i].getTime());
        machine.push_back(avail_machine); push_heap(machine.begin(), machine.end(), greater<int>());
    }
}

void testMakeSchedule(){
    int num_machine = 3;
    int num_job = 10;
    vector<machineNode> machine;
    vector<jobNode> job;
    for (int i = 0; i < num_machine; i++){
        machine.push_back(machineNode(i, 0));
    }
	for (int i = 0; i < num_job; i++){
        job.push_back(jobNode(i, 2 * i * i));
    }
    makeSchedule(job, machine, num_job, num_machine);
}

int main(){
    testMakeSchedule();
    return 0;
}
