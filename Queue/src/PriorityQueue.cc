/**@file PriorityQueue.cc
 * @author Caleb Reister <calebreister@gmail.com>
 */

#include "PriorityQueue.hh"
using namespace std;

PriorityQueue::PriorityQueue() {
    LEVELS = 10;
    schedule = new std::queue<Process>[LEVELS];
}

PriorityQueue::PriorityQueue(uint32_t priorities) {
    LEVELS = priorities;
    schedule = new std::queue<Process>[LEVELS];
}

PriorityQueue::~PriorityQueue() {
    delete [] schedule;
}

void PriorityQueue::push(Process add) {
    schedule[add.priority].push(add);
}

void PriorityQueue::push(queue<Process>& source, const uint32_t& clock) {
    Process newProcess;
    static uint32_t nextPID = 0;

    newProcess = source.front();
    source.pop();

    newProcess._pid = nextPID;
    newProcess._startTime = clock;

    nextPID++;
    this->push(newProcess);
}

Process* PriorityQueue::getNext() {
    uint32_t i = 0;
    while (schedule[i].empty())
    {
        if (i == LEVELS)
            return NULL;
        i++;
    }

    Process* output = new Process;
    *output = schedule[i].front();
    schedule[i].pop();
    return output;
}

bool PriorityQueue::empty() {
    for (uint32_t i = 0; i < LEVELS; i++)
        if (!schedule[i].empty())
            return false;
    return true;
}

uint32_t PriorityQueue::getPriorities() {
    return LEVELS;
}
