#include "PriorityQueue.hpp"
#include <iostream>

void swap(PatientNode *z, PatientNode *x);
PriorityQueue::PriorityQueue(int size) {
    maxQueueSize = size;
    currentQueueSize = 0;
    priorityQueue = new PatientNode[maxQueueSize+1];
}

PriorityQueue::~PriorityQueue() {
    delete [] priorityQueue;
}

PatientNode makeNode(std::string _name, int _injurySeverity, int _treatmentTime) {
    PatientNode p1;
    p1.name = _name;
    p1.injurySeverity = _injurySeverity;
    p1.treatmentTime = _treatmentTime;
    return p1;
}

//couldn't get a while loop implementation to work 100%
// void PriorityQueue::repairUpward(int nodeIndex) {
//     int parent = nodeIndex / 2;
//     while (parent > 0 && (priorityQueue[parent].injurySeverity < priorityQueue[nodeIndex].injurySeverity || (priorityQueue[parent].injurySeverity == priorityQueue[nodeIndex].injurySeverity && priorityQueue[parent].treatmentTime > priorityQueue[nodeIndex].treatmentTime))) {
//         swap(&priorityQueue[parent], &priorityQueue[nodeIndex]);
//         parent = parent / 2;
//     }
// }

void PriorityQueue::repairUpward(int nodeIndex) {
    int p = nodeIndex / 2;
    if(p > 0 && (priorityQueue[p].injurySeverity < priorityQueue[nodeIndex].injurySeverity || (priorityQueue[p].injurySeverity == priorityQueue[nodeIndex].injurySeverity && priorityQueue[p].treatmentTime > priorityQueue[nodeIndex].treatmentTime))) {
        swap(&priorityQueue[p],&priorityQueue[nodeIndex]);
        repairUpward(p);
    }
}

void PriorityQueue::enqueue(std::string _name, int _injurySeverity, int _treatmentTime) {
    currentQueueSize++;
    PatientNode node = makeNode(_name,_injurySeverity,_treatmentTime);
    priorityQueue[currentQueueSize] = node;
    repairUpward(currentQueueSize);
    // for(int i=1;i<=currentQueueSize;i++) {
    //     std::cout<<i<<":"<<priorityQueue[i].name<<std::endl;
    // }
    // std::cout << std::endl;
}

std::string PriorityQueue::peekName() {
    return priorityQueue[1].name;
}

int PriorityQueue::peekInjurySeverity() {
    return priorityQueue[1].injurySeverity;
}

int PriorityQueue::peekTreatmentTime() {
    return priorityQueue[1].treatmentTime;
}

void PriorityQueue::repairDownward(int nodeIndex) {
    int left = 2*nodeIndex;
    int right = 2*nodeIndex +1;

    int big_one = nodeIndex;

    if((left <= currentQueueSize) && ((priorityQueue[left].injurySeverity > priorityQueue[big_one].injurySeverity) || (priorityQueue[left].injurySeverity == priorityQueue[big_one].injurySeverity && priorityQueue[left].treatmentTime < priorityQueue[big_one].treatmentTime))) {
        big_one = left;
    }
    if((right <= currentQueueSize) && ((priorityQueue[right].injurySeverity > priorityQueue[big_one].injurySeverity) || (priorityQueue[right].injurySeverity == priorityQueue[big_one].injurySeverity && priorityQueue[right].treatmentTime < priorityQueue[big_one].treatmentTime))) {
        big_one = right;
    }

    if(big_one != nodeIndex) {
        swap(&priorityQueue[big_one], &priorityQueue[nodeIndex]);
        repairDownward(big_one);
    }
}

void PriorityQueue::dequeue() {
    if(currentQueueSize == 1) {
        currentQueueSize--;
        return ;
    }
    else {
        priorityQueue[1] = priorityQueue[currentQueueSize];
        currentQueueSize--;
        repairDownward(1);
    }
}

bool PriorityQueue::isFull() {
    if(currentQueueSize == maxQueueSize) {
        return true;
    }
    else {
        return false;
    }
}

bool PriorityQueue::isEmpty() {
    if(currentQueueSize == 0) {
        return true;
    }
    else {
        return false;
    }
}

// void swap(PatientNode &x, PatientNode &y)
// {
//     PatientNode temp = x;
//     x = y;
//     y = temp;
// }

void swap(PatientNode *z, PatientNode *x)
{
    PatientNode temp = *z;
    *z = *x;
    *x = temp;
}